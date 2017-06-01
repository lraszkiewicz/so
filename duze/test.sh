a="`dd bs=10 count=1 if=/dev/urandom``dd bs=100 count=1 if=/dev/zero``dd bs=10 count=1 if=/dev/urandom`"
echo $a > test.txt
