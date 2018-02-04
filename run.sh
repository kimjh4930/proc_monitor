#!/bin/bash

cpufreq=( 1400000 1300000 1200000 1100000 1000000 900000 800000 700000 600000 500000 400000 300000 200000 )

echo userspace > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
echo userspace > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed

for cpu in ${cpufreq[*]};
do
	echo 300000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
	echo 300000 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed

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
	#{ time "./cpubomb.sh"; } 2> time.txt

	./runtime ./run/cpubomb_10 1

	echo 300000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
	echo 300000 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
done

