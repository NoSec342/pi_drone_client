#!/bin/bash
# INSTALLATION SCRIPT FOR pi_drone_client   

SOURCE_DIR=$(pwd)

cmake ./ -B ./build
cd build/ 
make
cd ..
if [ $EUID == "0" ];then
    ln -s "$SOURCE_DIR/build/pi_drone_client" /usr/bin/pi_drone_client
    
else
    sudo ln -s "$SOURCE_DIR/build/pi_drone_client" /usr/bin/pi_drone_client
fi
echo "Installation Done!"
