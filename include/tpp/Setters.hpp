#pragma once

#include "../Setters.hpp"

namespace SCT::ArgsP::Setters
{
	template<>
	SCT_ArgsP_INL Error::Code
		parse<IntBase::automatic>(int64_t& v, std::string_view new_value)
	{
		std::string_view w_nv;
		int b = 10;
		if ((new_value[1] == 'b' || new_value[1] == 'B') && new_value[0] == '0')
		{
			w_nv = new_value.substr(2);
			b = 2;
		}
		else if ((new_value[1] == 'x' || new_value[1] == 'X') && new_value[0] == '0')
		{
			w_nv = new_value.substr(2);
			b = 16;
		}
		else
		{
			w_nv = new_value;
		}

		auto res = str_to<int64_t>(w_nv, nullptr, b);
		if (res)
		{
			v = res.value_or();
			return Error::Code::no_error;
		}

		return res.error();
	}

	template<IntBase base>
	SCT_ArgsP_INL Error::Code parse(int64_t& v, std::string_view new_value)
	{
		auto res = str_to<int64_t>(new_value, nullptr, static_cast<int>(base));
		if (res)
		{
			v = res.value_or();
			return Error::Code::no_error;
		}

		return res.error();
	}
}
