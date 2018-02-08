#!/bin/bash

cpufreq=( 200000 300000 400000 500000 600000 700000 800000 900000 1000000 1100000 1200000 1300000 1400000 )

#util=( 10 20 30 40 50 60 70 80 90 100 )

cpubomb=( cpubomb_10 cpubomb_20 cpubomb_30 cpubomb_40 cpubomb_50 cpubomb_60 cpubomb_70 cpubomb_80 cpubomb_90 cpubomb_100 )

echo userspace > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
echo userspace > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed

for cpubomb in ${cpubomb[*]};
do
	for cpu in ${cpufreq[*]};
	do
		echo 200000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		echo 200000 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
	
		sleep 5
	
		#set CPUFREQ
		#echo ${cpu} > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		echo ${cpu} > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
	
		#cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq
		cat /sys/devices/system/cpu/cpu4/cpufreq/cpuinfo_cur_freq
	
		#do benchmark

		echo ${cpubomb}
		cat /sys/devices/system/cpu/cpu4/cpufreq/cpuinfo_cur_freq >> ./result/big_ipc/${cpubomb}.txt
		./exec "./run/${cpubomb}" 2> /proc/taskpid
		dmesg -c >> ./result/big_ipc/${cpubomb}.txt
		dmesg -c >> ./result/big_ipc/${cpubomb}.txt

		echo "=========================="
		
		echo 200000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		echo 200000 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
	done
done

sleep 5
