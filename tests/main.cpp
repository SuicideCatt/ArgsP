#include <ArgsP.hpp>

#include <cassert>
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
	auto t = [](const SCT::ArgsP::ArgV& argv)
	{
		using namespace SCT::ArgsP;

		Flag::Bool help({{1, "h"}, {2, "help"}});
		Arguments::String path;
		Parameters::UInt64 res_w({{1, "w"}, {2, "res_w"}}, 100);
		Parameters::UInt64 res_h({{1, "h"}, {2, "res_h"}}, 100);
		Parameters::Double scale({{1, "s"}, {2, "scale"}}, 1.0);

		Parser p('-', false);

		p.add_arguments(help, path, res_w, res_h, scale);

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
			return false;
		}

		std::cout << *program << ":\n";
		std::cout << "  help(bool):   " << *help << '\n';
		std::cout << "  path(string): " << std::quoted(path.value_or("")) << '\n';
		std::cout << "  res_w(uint):   " << *res_w << '\n';
		std::cout << "  res_h(uint):   " << *res_h << '\n';
		std::cout << "  scale(double):   " << *scale << '\n';

		std::cout << '\n';
		return true;
	};

	assert(t({"test0", "-", "--", "---"})); // ignore test

	assert(t({"test1", "-h", "-w=1z2", "/path", "-h", "120"}) == false);
	assert(t({"test2", "--help", "--res_w=12", "/path", "--res_h", "120"}));
	assert(t({"test3", "--help", "/path", "--res_h", "120"}));
	assert(t({"test4", "-w", "120"}));
	assert(t({"test5", "-w", "1"})); // small int check

	// "-h=2" fails because first variant of "-h" first variant "-h" is bool flag,
	// parser expects it to be used without a value.
	assert(t({"test6", "-h=2", "123"}) == false);

	// "-w" is usigned int parameter
	assert(t({"test7", "-h", "-w=123.f"}) == false);
	assert(t({"test8", "-w=-123"}) == false);

	assert(t({"test9", "-w", "0b011"})); // binary!
	assert(t({"test10", "-w", "0xF"})); // hex!

	assert(t({"test11", "-s", "10.10"})); // floating!

	return 0;
}
