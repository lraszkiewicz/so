#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

int get_pm_endpt(endpoint_t *pt) {
  return minix_rs_lookup("pm", pt);
}

int myps(int uid) {
  endpoint_t pm_pt;
  if (get_pm_endpt(&pm_pt) != 0) {
    errno = ENOSYS;
    return -1;
  }

  message m;
  m.m1_i1 = uid;
  return (_syscall(pm_pt, PM_MYPS, &m));
}
