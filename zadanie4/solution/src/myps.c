#include "pm.h"
#include "proto.h"
#include "mproc.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int do_myps(void) {
  uid_t uid = m_in.m1_i1;

  if (uid == 0) {
    uid = mp->mp_realuid;
  }
  printf("PID\tPPID\tUID\r\n");
  for (int i = 0; i < NR_PROCS; ++i) {
    if (mproc[i].mp_pid != 0 && uid == mproc[i].mp_realuid) {
      printf("%d\t%d\t%u\r\n",
             mproc[i].mp_pid,
             mproc[mproc[i].mp_parent].mp_pid,
             mproc[i].mp_realuid);
    }
  }
  return OK;
}
