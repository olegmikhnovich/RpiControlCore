# RpiControl Core [![Build Status](https://travis-ci.org/olegmikhnovich/RpiControlCore.svg?branch=master)](https://travis-ci.org/olegmikhnovich/RpiControlCore)

RpiControl is a platform for Raspbian. RpiControl lets you configure and manage your device remotely over your local network.

**[Project website](https://olegmikhnovich.github.io/rpicontrolproject)**

This project contains 3 modules

| Module        | Description     |
| ------------- |-----------------|
| [RpiControl Core](https://github.com/olegmikhnovich/RpiControlCore) | Engine |
| [RpiControl App](https://github.com/olegmikhnovich/RpiControl)      | Client application for macOS |
| [RpiControl Mobile](https://github.com/olegmikhnovich/RpiControlMobile)      | Client application for iOS |

## Requirements
* OS Raspbian Stretch or newer
* Raspberry Pi device

## Build engine
* Install [CMake](https://cmake.org/install/).
* Clone this repo
```sh
git clone https://github.com/olegmikhnovich/RpiControlCore
```
* Go to the folder
```sh
cd RpiControlCore
```
* Give execute permissions to install script
```sh
sudo chmod +x ./install.sh
```
* And run it
```sh
sudo ./install.sh
```
After this steps you should reboot your device.

## Old versions
**WARNING! DON'T USE LEGACY VERSIONS OF THIS PRODUCT!**

**LEGACY VERSIONS WILL BE DELETED SOON**

The platform has been completely rewritten! You can see old versions of the product at these links:

| Module        | Description     |
| ------------- |-----------------|
| [RpiControl](https://github.com/olegmikhnovich/RpiControl_legacy) | Engine (Legacy)|
| [RpiControl Portal](https://github.com/olegmikhnovich/RpiControlPortal_legacy)      | Web portal (Legacy)|
| [Dashboard](https://github.com/olegmikhnovich/RpiControlDashboard_legacy) | Client Dashboard (Legacy)|

## License
Copyright (c) Oleg Mikhnovich. All rights reserved.
Licensed under the [Apache-2.0](LICENSE) License.
