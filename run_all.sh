export NUM_THREADS=$(lscpu | grep '^CPU(s):'|cut -d: -f2|sed 's/\s//g')
echo "Setting NUM_THREADS to $NUM_THREADS"
cd ./build/set/
for p in ./*
do
	if [ ! -d $p -a -x $p ]
	then
		TIME=$($p|tail -1)
		echo $TIME $p
	fi
done | sort -n
