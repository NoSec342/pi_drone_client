#!/bin/bash
# INSTALLATION SCRIPT FOR pi_drone_client   

SOURCE_DIR=$(pwd)

cmake ./ -B ./build
cd build/ 
make
cd ..
if [ $EUID == "0" ];then
    ln -s "$SOURCE_DIR/build/pi_drone_client" /usr/bin/pi_drone_client
    systemctl link ./pidrn_clt.service
    systemctl enable pidrn_clt.service
    systemctl start pidrn_clt.service
else
    sudo ln -s "$SOURCE_DIR/build/pi_drone_client" /usr/bin/pi_drone_client
    sudo systemctl link ./pidrn_clt.service
    sudo systemctl enable pidrn_clt.service
    sudo systemctl start pidrn_clt.service
fi
echo "Installation Done!"
