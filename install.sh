#!/bin/bash
# INSTALLATION SCRIPT FOR pi_drone_client   

SOURCE_DIR=$(pwd)

cmake ./ -B ./build
cd build/ 
make
if [ $? -eq 0 ];then

	if [ $EUID == "0" ];then
		cd $SOURCE_DIR
		ln -s $SOURCE_DIR/build/pi_drone_client /usr/bin/pi_drone_client
	elif [ $? -eq 0 ];then
		cd $SOURCE_DIR
		sudo ln -s $SOURCE_DIR/build/pi_drone_client /usr/bin/pi_drone_client
	fi
fi
tput setaf 2; echo "Installation done!"
