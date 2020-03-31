* This is a forked version from (PeterPriority)[https://github.com/PetePriority/chicony-ir-toggle]
Original toggle only sets IR cam on, but does not enable the alternative frame mode which flashes the emitter to boost face detection performance, this method is based on Peter's finding on in a discussion from Howdy github repo.

# chicony-ir-toggle
This project aims to control the IR emitters of windows hello enabled IR cameras under Linux

## Installation

Using cmake
```
mkdir -p build
cd build
cmake ..
make
sudo make install
```

Using gcc
```
gcc main.c -o chicony-ir-toggle
```

## Usage

```
chicony-ir-toggle <on|off>
```

## Confirmed devices 
Multiple newer lenovo laptops with windows hello e.g.
* Thinkpad T490s
* Yoga S740
* 81XD Lenovo XiaoXinPro-13API 2019 
