#!/bin/bash

clear

#./hidtool write 2 7 128 0xff
#./hidtool write 1
#./hidtool read | head -n 4

#echo
#echo
#sleep 5

../usbclient/hidtool write 4 1
../usbclient/hidtool write 1
BYTES=`./64rnd.pl`

echo "Zufallsframe:"
echo $BYTES | fold -w 80
echo "Schreibe Frame..."
../usbclient/hidtool write $BYTES

echo
echo
echo "Lese Frame..."
../usbclient/hidtool read | head -n 4

