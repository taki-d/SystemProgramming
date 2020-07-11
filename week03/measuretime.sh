#!/bin/sh

gcc fgetc.c -o fgetc > /dev/null 2>&1
gcc fgets.c -o fgets > /dev/null 2>&1
gcc fwrite.c -o fwrite > /dev/null 2>&1
gcc write.c -o write > /dev/null 2>&1

echo -n "fgetc : "
for v in `seq 10`; do rm copyfile && ./fgetc file copyfile; done | awk '{sum+= $1} END { print sum/NR}'

echo "fgets 256
fgets 256000
fgets 5120000
fgets 64000000
fwrite 256
fwrite 256000
fwrite 5120000
fwrite 64000000
write 256
write 256000
write 5120000
write 64000000" | while read cmd val
do
echo -n "${cmd} ${val} byte : "
for v in `seq 50`; do rm copyfile && ./${cmd} file copyfile ${val}; done | awk '{sum+= $1} END { print sum/NR}'
done
