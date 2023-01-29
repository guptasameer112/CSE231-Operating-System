#! /bin/bash

cd linux-5.19.8
make mrproper
cp ../../../Artix-Installation/config-rev-9-gold .config
time make -j$(nproc) > output.txt
cd ..


