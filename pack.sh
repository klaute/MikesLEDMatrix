#!/bin/bash

cd ..

DATE=`date -I | sed 'N;s/\n//'`

7za -xr\!MikesLEDMatrix/Entwuerfe a ~/Desktop/firmware_mikesledmatrix_$DATE.7z MikesLEDMatrix

cd -

cd ~/Desktop

7za x firmware_mikesledmatrix_$DATE.7z

tar cvzf firmware_mikesledmatrix_$DATE.tgz MikesLEDMatrix

rm -rf MikesLEDMatrix

cd -

