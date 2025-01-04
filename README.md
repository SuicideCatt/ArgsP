# ArgsP

Simple arguments parser for C++20.

## Usage
- Exceptions
	```cpp
	// In this example, all errors are thrown as exceptions.

	#include <ArgsP.hpp>
	#include <iostream>
	#include <iomanip>

	int main(int argc, char** argv)
	{
		using namespace SCT::ArgsP;

		// first parameter is prefix symbol count
		Parameters::Int64 res_h({Base::Info{1, "h"}});
		// default value
		Parameters::Int64 res_w({{1, "w"}}, 100);
		// multiple names for same flag
		Flag::Bool help({{1, "h"}, {2, "help"}});
		// capture argument without flag or parameter prefix
		Arguments::String path = "/tmp/test.html";

		// prefix symbol is '-'
		Parser p = '-';
		p.add_arguments(help, path, res_w, res_h);

		auto program = p.parse(argc, argv);
		std::cout << *program << ":\n";
		std::cout << "  help(bool):   " << *help << '\n';
		std::cout << "  path(string): " << std::quoted(*path) << '\n';
		std::cout << "  res_w(int):   " << *res_w << '\n';
		std::cout << "  res_h(int):   " << *res_h << '\n';
		std::cout << '\n';

		return 0;
	}
	```
- Error code
	```cpp
	// ...

	// If the no-exceptions compile flag is used,
	// this parameter is always false.
	Parser p('-', false);
	p.add_arguments(help, path, res_w, res_h);

	auto program = p.parse(argc, argv);
	if (p.error())
	{
		// ArgsP::Error::Exception is a subclass of std::system_error
		const ArgsP::Error::Exception& ex = p.get_error_container().get_error();

		// Print error
		if (error.argument.size()) // maybe ""
			std::cout << error.argument << '=';
		std::cout << std::quoted(error.value);
		std::cout << ": " << error.code().message() << '\n';
		// Or use std::exception::what();
		std::cout << "what(): " << error.what() << '\n';

		return 1;
	}

	std::cout << *program << ":\n";
	std::cout << "  help(bool):   " << *help << '\n';
	std::cout << "  path(string): " << std::quoted(*path) << '\n';
	std::cout << "  res_w(int):   " << *res_w << '\n';
	std::cout << "  res_h(int):   " << *res_h << '\n';
	std::cout << '\n';

	return 0;
	// ...
	```

Execution examples:
-	```
	$ ./test --help
	./test:
	  help(bool):   1
	  path(string): "/tmp/test.html"
	  res_w(int):   100
	  res_h(int):   0
	```
-	```
	$ ./test -h /test
	./test:
	  help(bool):   1
	  path(string): "/test"
	  res_w(int):   100
	  res_h(int):   0
	```
-	```
	$ ./test /test -w=10 -h 600
	./test:
	  help(bool):   0
	  path(string): "/test"
	  res_w(int):   10
	  res_h(int):   600
	```

## Download or Install
- [You can download one header version!](https://github.com/SuicideCatt/ArgsP/releases/latest)
- Debian package available on [releases](https://github.com/SuicideCatt/ArgsP/releases/latest)

	```bash
	$ curl -o ArgsP.deb -L $URL
	# dpkg -i ArgsP.deb
	```
- ArchLinux package available on [AUR](https://aur.archlinux.org/packages/sct_argsp)

	```bash
	$ yay -S sct_argsp
	```

## Adding a custom parameter/argument
- Simple and flexible approach (passing a function for standard types)
	```cpp
	#include <ArgsP.hpp>

	namespace ArgsP = SCT::ArgsP;

	struct Resolution
	{
	    int width, height;
	};

	// Creates a function for parsing a string to value
	ArgsP::Error::Code parse_resolution(Resolution& value, std::string_view new_value)
	{
		auto i = new_value.find('x');
		if (i == new_value.npos) // Returns an error if 'x' symbol is missing
			return ArgsP::Error::Code::syntax_error;

		// Uses alternative to std::stoi. Doesn't throw errors;
		// just returns either error or a value
		auto width = ArgsP::str_to<uint32_t>(new_value.substr(0, i));
		if (!width.has_value())
			return width.error();

		auto height = ArgsP::str_to<uint32_t>(new_value.substr(i + 1));
		if (!height)
			return height.error();

		value.width = width.value_or();
		value.height = height.value_or();

		return ArgsP::Error::Code::no_error;
	}

	// Uses the default Parameter/Argument implementation and parse function
	using ResolutionParameter = ArgsP::Base::Parameter<Resolution, &parse_resolution>;
	using ResolutionArgument = ArgsP::Base::Argument<Resolution, &parse_resolution>;

	// ...
	```
- Less flexible approach (creating a subclass with custom parsing logic)
	```cpp
	// ...

	// Creates subclass of default Parameter
	struct ResolutionParameter : ArgsP::Base::Parameter<Resolution>
	{
		ResolutionParameter(Infos names, Resolution base = {100, 100})
			: ArgsP::Base::Parameter<Resolution>(names, base) {}

		// Overrides the 'parse_value' method to parse the resolution
		// Default 'parse_value' tries to call the parse function
		ArgsP::Error::Code parse_value(std::string_view new_value) override
		{
			auto i = new_value.find('x');
			if (i == new_value.npos)
				return ArgsP::Error::Code::syntax_error;

			auto width = ArgsP::str_to<uint32_t>(new_value.substr(0, i));
			if (!width)
				return width.error();

			auto height = ArgsP::str_to<uint32_t>(new_value.substr(i + 1));
			if (!height)
				return height.error();

			// 'p_value' is defined in the parent class.
			p_value.width = width.value_or();
			p_value.height = height.value_or();

			return ArgsP::Error::Code::no_error;
		}
	};

	// ...
	```

## TODO
- [ ] Add RPM package
- [x] Add Arch package

