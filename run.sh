#!/bin/bash

cpufreq=( 1400000 1300000 1200000 1100000 1000000 900000 800000 700000 600000 500000 400000 300000 200000 )

util=( 100 90 80 70 60 50 40 30 20 10 )

echo userspace > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
echo userspace > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed

for u in ${util[*]};
do
	for cpu in ${cpufreq[*]};
	do
		echo 200000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		echo 200000 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
	
		sleep 5
	
		#set CPUFREQ
		echo ${cpu} > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		echo ${cpu} > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
	
		echo "=========================="
		cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq
		cat /sys/devices/system/cpu/cpu1/cpufreq/cpuinfo_cur_freq
		cat /sys/devices/system/cpu/cpu2/cpufreq/cpuinfo_cur_freq
		cat /sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_cur_freq
		cat /sys/devices/system/cpu/cpu4/cpufreq/cpuinfo_cur_freq
		cat /sys/devices/system/cpu/cpu5/cpufreq/cpuinfo_cur_freq
		cat /sys/devices/system/cpu/cpu6/cpufreq/cpuinfo_cur_freq
		cat /sys/devices/system/cpu/cpu7/cpufreq/cpuinfo_cur_freq
	
		#do benchmark
	
		#{ time "./iozone.sh"; } 2> time.txt
		#{ time "./sysbench.sh"; } 2> time.txt

		echo cpubomb_${u} >> ./result/big/t1/${u}_time.txt
		{ time ./run/cpubomb_${u} 1 ; } 2> time.txt
		cat time.txt >> ./result/big/t1/${u}_time.txt
		echo "==========" >> ./result/big/t1/${u}_time.txt
	
		echo 200000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		echo 200000 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
	done
done

sleep 5
