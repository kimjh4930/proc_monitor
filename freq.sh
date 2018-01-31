freq=( 200000 300000 400000 500000 600000 700000 800000 900000 1000000 1100000 1200000 1300000 1400000 )

#freq=( 500000 1000000 1400000 )

echo ${freq[$1]} > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
echo ${freq[$1]} > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed

cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
cat /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed
