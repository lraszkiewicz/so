qemu-system-x86_64 -curses -drive file=so.img -localtime -net user,hostfwd=tcp::4242-:22 -net nic,model=virtio -m 1024M
