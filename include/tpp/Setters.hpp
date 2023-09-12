#pragma once

#include "../Setters.hpp"

namespace SCT::ArgsP::Setters
{
	template<>
	SCT_ArgsP_INL void parse<0>(int64_t& v, const std::string_view& nv)
	{
		std::string w_nv;
		int b = 0;
		if ((nv[1] == 'b' || nv[1] == 'B') && nv[0] == '0')
		{
			w_nv = nv.substr(2);
			b = 2;
		}
		else
		{
			w_nv = nv;
		}

		v = std::stoll(w_nv, nullptr, b);
	}

	template<int B>
	SCT_ArgsP_INL void parse(int64_t& v, const std::string_view& nv)
		{ v = std::stoll(std::string(nv), nullptr, B); }
}
