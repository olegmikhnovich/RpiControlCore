#!/bin/bash

# Copyright (c) Oleg Mikhnovich. All rights reserved.
# Licensed under the Apache-2.0 License.

# install.sh

# -> Setup dirs
CONFIG_FOLDER=/etc/rpicontrol
APP_FOLDER=/usr/bin

# Cleanup if exists
sudo rm -rf $CONFIG_FOLDER
sudo rm $APP_FOLDER/RpiControlCore

# -> Create config folder
sudo mkdir $CONFIG_FOLDER

# -> Create device name
printf 'pi' | sudo tee  $CONFIG_FOLDER/devicecredname.conf
# -> Create device password
# Warn! You should change the password after first login.
printf 'raspberry' | sudo tee $CONFIG_FOLDER/devicecredpwd.conf

# -> Build and install
rm -rf ./build
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release ../
cmake --build . -- -j4

sudo mv ./RpiControlCore $APP_FOLDER

# -> Cleanup build
cd ..
rm -rf ./build

# Set script as a service
SERVICE_PATH=/lib/systemd/system/rpicontrol.service

printf '[Unit]\nDescription=RpiControl Service\nAfter=network.target\nStartLimitIntervalSec=0\n\n[Service]\nType=simple\nRestart=always\nRestartSec=1\nUser=root\nExecStart=/usr/bin/RpiControlCore\n\n[Install]\nWantedBy=multi-user.target' | sudo tee $SERVICE_PATH
sudo chmod 644 $SERVICE_PATH

sudo systemctl start rpicontrol.service
sudo systemctl enable rpicontrol.service
sudo systemctl daemon-reload