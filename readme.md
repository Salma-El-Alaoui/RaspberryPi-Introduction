##Set up

#### Compile QEMU for ARM (On Ubuntu 11+)

* First you will need to install the following packages:
```
sudo apt-get install git zlib1g-dev libsdl1.2-dev
sudo apt-get install libpixman-1-dev libfdt-dev
```
* Downloading
```
git clone https://github.com/Torlus/qemu.git
git fetch origin
git checkout -b raspberry origin/rpi
git fetch
git checkout raspberry
```
* Configuring and Compiling
```
cd qemu 
./configure --target-list="arm-softmmu arm-linux-user" --enable-sdl --prefix=/usr --disable-werror
make
sudo make install 
```
You should now have a working QEMU install.

### Install the compiler

It can be installed through this ppa:
```
sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded
sudo apt-get update
sudo apt-get install gcc-arm-none-eabi
```
You should now be able to run the program and debug using GDB.

### Run
```
make
cd debug
./run-qemu.sh
```
In another terminal window:
```
cd debug
./run-gdb.sh
```


`
