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

### How to use
```cpp
namespace Args = SCT::ArgsP::Arguments;
namespace Flags = SCT::ArgsP::Flags;

// ...

SCT::ArgsP::Parser p = '-';

// V1
	Args::String::SPtr a_str(new Args::String("base_value"));
// V2
	Args::String::SPtr a_str(new Args::String()); // base value is ""

// V1
	Args::Int64::SPtr a_i(new Args::Int64(7));
// V2
	Args::Int64::SPtr a_i(new Args::Int64()); // base value is 0

// V1
	Flags::String::SPtr f_str(new Flags::String({{1, "str"}, {2, "string"}}, "empty"));
// V2
	Flags::String::SPtr f_str(new Flags::String({{1, "str"}, {2, "string"}})); // base is ""

// V1
	Flags::Int64::SPtr f_i(new Flags::Int64({{1, "i"}, {2, "int"}}, 7));
// V2
	Flags::Int64::SPtr f_i(new Flags::Int64({{1, "i"}, {2, "int"}})); // base is 0

// V1
	Flags::Bool::SPtr f_b(new Flags::Bool({{1, "b"}, {2, "bool"}}, true));
// V2
	Flags::Bool::SPtr f_b(new Flags::Bool({{1, "b"}, {2, "bool"}})); // base is false

// V1
	p.add_arguments(a_str, a_i, f_str, f_i, f_b);
// V2
	p.add_argument(a_str);
	p.add_argument(a_i);
	p.add_argument(f_str);
	// ...
	
std::cout << "prog: " << p.parse(args, argv) << '\n'; // Print executable file name
std::cout << "  a_str: " << a_str->get() << '\n';
std::cout << "  a_i: " << a_i->get() << '\n';
std::cout << "  f_str: " << f_str->get() << '\n';
std::cout << "  f_i: " << f_i->get() << '\n';
std::cout << "  f_b: " << f_b->get() << '\n';
```
