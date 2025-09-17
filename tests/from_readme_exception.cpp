#include <ArgsP.hpp>
#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
	using namespace SCT::ArgsP;

	// first parameter is prefix symbol count
	// NOTE: default is std::nullopt
	Parameters::Int64 res_h({Base::Info{1, "h"}});
	// default value is 100
	Parameters::Int64 res_w({{1, "w"}}, 100);
	// multiple names for same flag
	Flag::Bool help({{2, "help"}});
	// capture argument without flag or parameter prefix
	Arguments::String path("/tmp/test.html");

	// prefix symbol is '-'
	Parser p = '-';
	p.add_arguments(help, path, res_w, res_h);

	auto program = p.parse(argc, argv);
	std::cout << *program << ":\n";
	std::cout << "  help(bool):   " << *help << '\n';
	std::cout << "  path(string): " << std::quoted(*path) << '\n';
	std::cout << "  res_w(int):   " << *res_w << '\n';
	std::cout << "  res_h(int):   " << res_h.value_or(0) << '\n';
	std::cout << '\n';

	return 0;
}
