echo userspace > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
echo userspace > /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor

echo 0 > /sys/devices/system/cpu/cpu1/online
echo 0 > /sys/devices/system/cpu/cpu2/online
echo 0 > /sys/devices/system/cpu/cpu3/online
echo $1 > /sys/devices/system/cpu/cpu4/online
echo $2 > /sys/devices/system/cpu/cpu5/online
echo $3 > /sys/devices/system/cpu/cpu6/online
echo $4 > /sys/devices/system/cpu/cpu7/online
