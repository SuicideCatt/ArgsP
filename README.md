# ArgsP
C++ Arguments parser

### Build
Dependents:
- Git
- CMake
- C++ 20

Step 1: Download
```bash
git clone https://github.com/SuicideCatt/ArgsP
cd ArgsP
mkdir build
cd build
```

Step 2: Linux
```bash
$ cmake ..
$ make -j$(nproc)
# make install
```

### Only headers mode:
Step 1: No build but install on Linux 
```bash
$ cmake .. -DSCT_NO_BUILD
# make install
```
And Step 2: 
```cpp
#define USE_SCT_ArgsP_HM
#include <SCT/ArgumentsParser/ArgumentsParser.hpp>
```
