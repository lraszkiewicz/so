username=`dd bs=1 count=13 skip=1024 if=/dev/c0d0 2> /dev/null`
id -u $username > /dev/null 2> /dev/null
if [ $? -ne 0 ]
then
    user add -m -g users $username
fi
su -Kl $username

# Login shell profile.

umask 022

# Favourite editor and pager, search path for binaries, etc.
export EDITOR=vi
export PAGER=less

# Let cd display the current directory on the status line.
if [ -t 0 -a -f /usr/bin/tget ] && tget -flag hs
then
case $- in *i*)
	hostname=$(expr $(uname -n) : '\([^.]*\)')
	eval "cd()
	{
		chdir \"\$@\" &&
		echo -n '$(tget -str ts \
				"$USER@$hostname:'\"\`pwd\`\"'" \
				-str fs)'
	}"
	unset hostname
	cd .
	;;
esac
fi

# Check terminal type.
case $TERM in
dialup|unknown|network)
	echo -n "Terminal type? ($TERM) "; read term
	TERM="${term:-$TERM}"
	unset term
esac
