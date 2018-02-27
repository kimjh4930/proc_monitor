#!/bin/bash

#little
#cpufreq=( 200000 300000 400000 500000 600000 700000 800000 900000 1000000 1100000 1200000 1300000 1400000 )

#big
cpufreq=( 200000 300000 400000 500000 600000 700000 800000 900000 1000000 1100000 1200000 1300000 1400000 1500000 1600000 1700000 1800000 1900000 2000000)

util=( 90 80 70 60 50 40 30 20 10 )

echo userspace > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
#echo userspace > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed

for u in ${util[$1]};
do
	for cpu in ${cpufreq[*]};
	do

		echo 0 > /sys/devices/system/cpu/cpu1/online
		echo 0 > /sys/devices/system/cpu/cpu2/online
		echo 0 > /sys/devices/system/cpu/cpu3/online
		echo 1 > /sys/devices/system/cpu/cpu4/online
		echo 0 > /sys/devices/system/cpu/cpu5/online
		echo 0 > /sys/devices/system/cpu/cpu6/online
		echo 0 > /sys/devices/system/cpu/cpu7/online

		cat /sys/devices/system/cpu/online

		echo 200000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		echo 200000 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
	
		sleep 5
	
		#set CPUFREQ
		#echo ${cpu} > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		echo ${cpu} > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
	
		echo "=========================="
		cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq
		#cat /sys/devices/system/cpu/cpu1/cpufreq/cpuinfo_cur_freq
		#cat /sys/devices/system/cpu/cpu2/cpufreq/cpuinfo_cur_freq
		#cat /sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_cur_freq
		cat /sys/devices/system/cpu/cpu4/cpufreq/cpuinfo_cur_freq
		#cat /sys/devices/system/cpu/cpu5/cpufreq/cpuinfo_cur_freq
		#cat /sys/devices/system/cpu/cpu6/cpufreq/cpuinfo_cur_freq
		#cat /sys/devices/system/cpu/cpu7/cpufreq/cpuinfo_cur_freq
	
		#do benchmark
	
		#{ time "./iozone.sh"; } 2> time.txt
		#{ time "./sysbench.sh"; } 2> time.txt

		echo cpubomb_${u}

		./runtime ./cpubomb/watt/cpubomb_${u} 1
	
		echo 200000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		echo 200000 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
		cat /sys/devices/system/cpu/online
	done
done

sleep 5
