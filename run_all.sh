cd ./build/set/
for p in ./*
do
	if [ ! -d $p -a -x $p ]
	then
		TIME=$($p|tail -1)
		echo $p $TIME
	fi
done
