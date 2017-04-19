cp src/Makefile src/myps.c src/proto.h src/table.c /usr/src/minix/servers/pm/
cp src/callnr.h /usr/include/minix/
cp src/callnr.h /usr/src/minix/include/minix/
cp src/unistd.h /usr/include/
cp src/unistd.h /usr/src/include/
cp src/Makefile.inc /usr/src/lib/libc/misc/
cp src/myps_lib.c /usr/src/lib/libc/misc/myps.c
cd /usr/src/releasetools
make hdboot
reboot
