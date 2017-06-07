#include <minix/drivers.h>
#include <minix/chardriver.h>
#include <stdio.h>
#include <stdlib.h>
#include <minix/ds.h>
#include "helloN.h"

/*
 * Function prototypes for the helloN driver.
 */
static int helloN_open(devminor_t minor, int access, endpoint_t user_endpt);
static int helloN_close(devminor_t minor);
static ssize_t helloN_read(devminor_t minor, u64_t position, endpoint_t endpt,
    cp_grant_id_t grant, size_t size, int flags, cdev_id_t id);
static ssize_t helloN_write(devminor_t minor, u64_t position, endpoint_t endpt,
    cp_grant_id_t grant, size_t size, int flags, cdev_id_t id);

/* SEF functions and variables. */
static void sef_local_startup(void);
static int sef_cb_init(int type, sef_init_info_t *info);
static int sef_cb_lu_state_save(int);
static int lu_state_restore(void);

/* Entry points to the helloN driver. */
static struct chardriver helloN_tab =
{
    .cdr_open   = helloN_open,
    .cdr_close  = helloN_close,
    .cdr_read   = helloN_read,
    .cdr_write  = helloN_write,
};

/* The buffer of the helloN driver. */
static char buffer[DEVICE_SIZE];

static int helloN_open(devminor_t UNUSED(minor), int UNUSED(access),
    endpoint_t UNUSED(user_endpt))
{
    return OK;
}

static int helloN_close(devminor_t UNUSED(minor))
{
    return OK;
}

static ssize_t helloN_read(devminor_t UNUSED(minor), u64_t position,
    endpoint_t endpt, cp_grant_id_t grant, size_t size, int UNUSED(flags),
    cdev_id_t UNUSED(id))
{
    char *ptr;
    int ret;

    /* Check for EOF, and possibly limit the read size. */
    if (position >= DEVICE_SIZE) return 0;  /* EOF */
    if (position + size > DEVICE_SIZE)
        size = (size_t)(DEVICE_SIZE - position);  /* limit size */

    /* Copy the requested part to the caller. */
    ptr = buffer + (size_t)position;
    if ((ret = sys_safecopyto(endpt, grant, 0, (vir_bytes) ptr, size)) != OK)
        return ret;

    /* Return the number of bytes read. */
    return size;
}

static ssize_t helloN_write(devminor_t UNUSED(minor), u64_t position,
    endpoint_t endpt, cp_grant_id_t grant, size_t size, int UNUSED(flags),
    cdev_id_t UNUSED(id))
{
    char *ptr;
    int ret;

    /* Check for EOF, and possibly limit the write size. */
    if (position >= DEVICE_SIZE) return 0;  /* EOF */
    if (position + size > DEVICE_SIZE)
        size = (size_t)(DEVICE_SIZE - position); /* limit size */

    /* Copy data from the caller to the driver's buffer. */
    ptr = buffer + (size_t) position;
    if ((ret = sys_safecopyfrom(endpt, grant, 0, (vir_bytes) ptr, size)) != OK)
        return ret;

    /* Return the number of saved bytes. */
    return size;
}

static int sef_cb_lu_state_save(int UNUSED(state)) {
/* Save the state. */
    ds_publish_mem("buffer", buffer, DEVICE_SIZE, DSF_OVERWRITE);

    return OK;
}

static int lu_state_restore() {
/* Restore the state. */
    size_t length = DEVICE_SIZE;
    ds_retrieve_mem("buffer", buffer, &length);
    ds_delete_mem("buffer");

    return OK;
}

static void sef_local_startup()
{
    /*
     * Register init callbacks. Use the same function for all event types
     */
    sef_setcb_init_fresh(sef_cb_init);
    sef_setcb_init_lu(sef_cb_init);
    sef_setcb_init_restart(sef_cb_init);

    /*
     * Register live update callbacks.
     */
    /* - Agree to update immediately when LU is requested in a valid state. */
    sef_setcb_lu_prepare(sef_cb_lu_prepare_always_ready);
    /* - Support live update starting from any standard state. */
    sef_setcb_lu_state_isvalid(sef_cb_lu_state_isvalid_standard);
    /* - Register a custom routine to save the state. */
    sef_setcb_lu_state_save(sef_cb_lu_state_save);

    /* Let SEF perform startup. */
    sef_startup();
}

static int sef_cb_init(int type, sef_init_info_t *UNUSED(info))
{
/* Initialize the helloN driver. */
    int do_announce_driver = TRUE;

    switch(type) {
        case SEF_INIT_FRESH:
            /* Initialize the driver's buffer. */
            for (int i = 0; i < DEVICE_SIZE; ++i)
            {
                buffer[i] = 'a';
            }
        break;

        case SEF_INIT_LU:
            /* Restore the state. */
            lu_state_restore();
            do_announce_driver = FALSE;
        break;

        case SEF_INIT_RESTART:
        break;
    }

    /* Announce we are up when necessary. */
    if (do_announce_driver) {
        chardriver_announce();
    }

    /* Initialization completed successfully. */
    return OK;
}

int main(void)
{
    /*
     * Perform initialization.
     */
    sef_local_startup();

    /*
     * Run the main loop.
     */
    chardriver_task(&helloN_tab);
    return OK;
}
