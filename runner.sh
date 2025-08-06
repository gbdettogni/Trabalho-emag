ps aux | grep octave > temppp
head -n 1  temppp | awk '{print $2}' > tempp
pkill -F tempp
gcc setter.c -o setterrr
./setter
sleep 1
rm setterrr temppp
mkoctfile -c main.cpp
mkoctfile --link-stand-alone -o prog main.o
octave main.m &
sleep 1
LD_LIBRARY_PATH=/lib/octave/10.2.0 ./prog