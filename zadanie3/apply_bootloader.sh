echo 'Compiling bootloader.asm'
nasm -f bin bootloader.asm
echo 'Copy MBR from sector 0 to sector 1'
dd bs=512 count=1 seek=1 if=/dev/c0d0 of=/dev/c0d0
echo 'Fill first 446 bytes of HD with 0s'
dd bs=1 count=446 if=/dev/zero of=/dev/c0d0
echo 'Fill sector 2 with 0s'
dd bs=512 count=1 seek=2 if=/dev/zero of=/dev/c0d0
echo 'Copy compiled bootloader.asm to HD start'
dd bs=1 if=bootloader of=/dev/c0d0
