#pragma once

#include "../Setters.hpp"

namespace SCT::ArgsP::Setters
{
	SCT_ArgsP_INL void parse(std::string_view &v, const std::string_view &nv)
		{ v = nv; }

	SCT_ArgsP_INL void parse(bool &v, const std::string_view &nv)
		{ v = !v; }
}
