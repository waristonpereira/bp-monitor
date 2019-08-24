# Blood Pressure Monitor Lib
## Table of Contents
* [About](#about)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Build for desktop](#build-for-desktop)
  * [Build for embedded (Raspberry PI v3)](#build-for-embedded)
* [Usage](#usage)
* [Contact](#contact)

### About

This project implements a library to find the systolic/diastolic pressures of the closest pulse in a vector based on a point selected by the user.

The vector is already processed, which means the data is filtered and formatted in mmHg. It contains the pulse pressure along the time representing an arterial blood pressure wave.

More info on doc folder.

`NOTICE: Instructions for Linux ecosystem like Ubuntu 19.04. Please adapt for your scenario. Thanks!`

## Getting Started

### Prerequisites

GIT for repo clone
```sh
$ sudo apt install git
```

Build needs C++11 standard compliant:
```sh
$ sudo apt install build-essential g++
```
Tests needs and CMake and [Google Tests(GTest)](https://github.com/google/googletest/) libs installed:
```sh
$ sudo apt install cmake
$ git clone https://github.com/google/googletest/ ~/googletest
$ cd ~/googletest
$ cmake CMakeLists.txt
$ make
$ sudo cp *.a /usr/lib
```

### Build for desktop

Clone lib repo:
```sh
$ git clone https://github.com/google/googletest/ ~/bp-monitor
```

Build:
```sh
$ cd ~/bp-monitor/src
$ make
```

Install on system libs:
```sh
$ sudo cp ~/bp-monitor/src/libbpmonitor.so /lib
$ sudo cp ~/bp-monitor/src/lib-monitor.h /usr/include
```

### Build for embedded

`NOTICE: Instructions for Raspberry PI v3. Please adapt for your scenario. Thanks!`

Clone lib repo:
```sh
$ git clone https://github.com/google/googletest/ ~/bp-monitor
```

Clone [BUILDROOT](https://github.com/buildroot/buildroot) repo:
```sh
$ git clone https://github.com/buildroot/buildroot ~/buildroot

```
The dir package contains the files necessary. Copy this to BUILDROOT:
```sh
$ cp -a ~/bp-monitor/package ~/buildroot

```
Edit the file `~/buildroot/packages/Config.in` and add these lines to enable lib as package on build:
```
menu "Target packages"
  ...
  # BP Monitor Package
  source "package/bp-monitor/Config.in"
  ...
```
To build package:
```sh
$ make bp-monitor
```

To build entire system:
```sh
$ make
```

## Usage

To use this library simple include header:
```c++
...
#include "bp-monitor.h"
...
```

Instantiate de `BP_MONITOR` class and call method `measure` passing as parameter the waveform buffer (as array of int), the size of the buffer, and the point index selected by user.

```c++
...
BP_MONITOR m;
BP result = m.measure(sample_array, number_of_samples, index_target);
...
```
The result return as BP struct like:
```c++
struct BP {
    int SBP;  // systolic blood pressure value measure
    int SBPi; // systolic blood pressure index at measure
    int DBP;  // diastolic blood pressure value measure
    int DBPi; // diastolic blood pressure index at measure
};
```

An error is trigger on:
* sample_array is empty.
* index_target > number_of_samples.
* impossible measure at target.

Example of use in folder [example](bp-monitor/example).

More info on [doc](bp-monitor/doc) folder.
