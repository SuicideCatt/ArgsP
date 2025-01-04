#include <ArgsP.hpp>

#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
	auto t = [](const SCT::ArgsP::ArgV& argv)
	{
		using namespace SCT::ArgsP;

		Flag::Bool help({{1, "h"}, {2, "help"}});
		Arguments::String path;
		Parameters::Int64 res_w({{1, "w"}, {2, "res_w"}}, 100);
		Parameters::Int64 res_h({{1, "h"}, {2, "res_h"}}, 100);

		Parser p('-', false);

		p.add_arguments(help, path, res_w, res_h);

		for (const auto& arg : argv)
			std::cout << arg << ' ';
		std::cout << '\n';

		auto program = p.parse(argv);
		if (p.error())
		{
			const auto& error = p.get_error_container().get_error();
			std::cout << "what(): " << error.what() << '\n';

			if (error.argument.size())
				std::cout << error.argument << '=';
			std::cout << std::quoted(error.value);
			std::cout << ": " << error.code().message() << '\n';

			std::cout << '\n';
			return;
		}

		std::cout << *program << ":\n";
		std::cout << "  help(bool):   " << *help << '\n';
		std::cout << "  path(string): " << std::quoted(*path) << '\n';
		std::cout << "  res_w(int):   " << *res_w << '\n';
		std::cout << "  res_h(int):   " << *res_h << '\n';

		std::cout << '\n';
	};

	t({"test1", "-h", "-w=1z2", "/path", "-h", "120"});
	t({"test2", "--help", "--res_w=12", "/path", "--res_h", "120"});
	t({"test3", "--help", "/path", "--res_h", "120"});
	t({"test4", "-w", "120"});

	t({"test5", "-h=2", "123"}); // error test
	t({"test6", "-h", "-w=123.f"}); // error test

	t({"test7", "-w", "0b011"}); // binary!
	t({"test8", "-w", "0xF"}); // hex!

	new int[10];

	return 0;
}
