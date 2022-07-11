IR marker tracker

---

# Overview

Infrared LED marker tracker for 3D position estimation.
This system uses a set of fisheye lens cameras capable of detecting infrared light and an infrared LED marker that blinks at a fixed period.


## Features
[ ] Marker detection using FIR
[ ] Marker position estimation
[ ] (option) Process optimization using CUDA


## Build

### Clone 

```shell
git clone --recursive git@github.com:aoiyu/ir-marker-tracker.git
```

### Build OpenCV (lib/opencv) using cmake-gui

If you want to write super long flags by hand, you can do that in the CUI.

In the gui

- Set build folder `lib/opencv/build`
- Press Configure
- Press Generate

```shell
cd lib/opencv/build
make -j 8 # 8 is the number of cores on your machine
```

### Build

```shell
cd ir-marker-tracker
mkdir build
cd build
cmake ..
```

## Run

```shell
cd build
./ir_marker_tracker
```