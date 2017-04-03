scp bootloader.asm apply_bootloader.sh so:~
ssh so chmod +x apply_bootloader.sh
echo 'Running apply_bootloader.sh'
ssh so ./apply_bootloader.sh
echo 'Turning off VM'
ssh so /sbin/poweroff
