# ArgsP
C++ Arguments parser

### Install
Dependents:
- Git
- CMake
- C++ 20

[AUR package](https://aur.archlinux.org/packages/sct_argsp)

#### Source
Step 1: Download
```bash
git clone https://github.com/SuicideCatt/ArgsP
cd ArgsP
```

Step 2 v1: Copy include folder to your thrid party folder
``` bash
cp include /path/to/include/ArgsP
```

Step 2 v2: Create folder for cmake cache
``` bash
mkdir build
cd build
```

Step 3: Install Linux or MSYS2
```bash
$ cmake ..
# make install
```
-- -
### How to use
```cpp
#include <SCT/ArgsP/ArgsP.hpp>

// ...

namespace Args = SCT::ArgsP::Arguments;
namespace Flags = SCT::ArgsP::Flags;

// ...

SCT::ArgsP::Parser p = '-';

// V1
	Args::String a_str("base_value");
// V2
	Args::String a_str; // base value is ""

// V1
	Args::Int64 a_i(7);
// V2
	Args::Int64 a_i; // base value is 0

// V1
	Flags::String f_str({{1, "str"}, {2, "string"}}, "empty");
// V2
	Flags::String f_str({{1, "str"}, {2, "string"}}); // base is ""

// V1
	Flags::Int64 f_i({{1, "i"}, {2, "int"}}, 7);
// V2
	Flags::Int64 f_i({{1, "i"}, {2, "int"}}); // base is 0

// V1
	Flags::Bool f_b({{1, "b"}, {2, "bool"}}, true);
// V2
	Flags::Bool f_b({{1, "b"}, {2, "bool"}}); // base is false

// V1
	p.add_arguments(a_str, a_i, f_str, f_i, f_b);
// V2
	p.add_argument(a_str);
	p.add_argument(a_i);
	p.add_argument(f_str);
	// ...
	
std::cout << "prog: " << p.parse(args, argv) << '\n'; // Print executable file name
std::cout << "  a_str: " << *a_str << '\n';
std::cout << "  a_i: " << *a_i << '\n';
std::cout << "  f_str: " << *f_str << '\n';
std::cout << "  f_i: " << *f_i << '\n';
std::cout << "  f_b: " << *f_b << '\n';
```
