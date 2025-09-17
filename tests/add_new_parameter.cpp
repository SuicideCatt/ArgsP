#include <ArgsP.hpp>
#include <iostream>

namespace ArgsP = SCT::ArgsP;

struct Resolution
{
    int width, height;
};

ArgsP::Error::Code
	parse_resolution(std::optional<Resolution>& value, std::string_view new_value)
{
	auto i = new_value.find('x');
	if (i == new_value.npos)
		return ArgsP::Error::Code::syntax_error;

	auto width =
		ArgsP::str_to<uint32_t>(new_value.substr(0, i));
	if (!width.has_value())
		return width.error();

	auto height =
		ArgsP::str_to<uint32_t>(new_value.substr(i + 1));
	if (!height)
		return height.error();

	auto& val = value.emplace();
	val.width = width.value_or(0);
	val.height = height.value_or(0);

	return ArgsP::Error::Code::no_error;
}

using ResolutionParameter = ArgsP::Parameters::Base<Resolution, &parse_resolution>;
using ResolutionArgument =  ArgsP::Arguments::Base<Resolution, &parse_resolution>;

struct AltResolutionParameter : ArgsP::Parameters::Base<Resolution>
{
	AltResolutionParameter(Infos names, OptType base = Resolution{100, 100})
		: Parameter(names, base) {}

	ArgsP::Error::Code parse_value(std::string_view new_value) override
		{ return parse_resolution(p_value, new_value); }
};

int main(int argc, char** argv)
{
	ArgsP::Parser p('-', false);

	ResolutionParameter res({{1, "r"}, {2, "res"}});
	AltResolutionParameter alt_res({{1, "ar"}, {2, "alt_res"}});
	p.add_arguments(res, alt_res);

	auto program = p.parse(argc, argv);
	if (p.error())
	{
		auto& err = p.get_error_container().get_error();

		std::cerr << err.what() << '\n';

		return 1;
	}

	std::cout << *program << ":\n";
	{
		auto r = res.value_or({});
		std::cout << "  res(WxH): " << r.width << 'x' << r.height << '\n';
	}
	const auto& alt_res_ref = *alt_res;
	std::cout << "  alt_res(WxH): " << alt_res_ref.width << 'x' << alt_res_ref.height << '\n';

	return 0;
}
