# Kill process shell
ps cax | grep $1 > /dev/null
if [ $? -eq 0 ]; then
  	killall -9 $1 || true
fi
