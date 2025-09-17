#pragma once

#include "../Setters.hpp"

namespace SCT::ArgsP::Setters
{
	SCT_ArgsP_INL Error::Code parse(std::optional<std::string_view>& v,
									std::string_view new_value)
	{
		v = new_value;
		return Error::Code::no_error;
	}

	SCT_ArgsP_INL Error::Code parse(std::string_view& v, std::string_view new_value)
	{
		v = new_value;
		return Error::Code::no_error;
	}

	SCT_ArgsP_INL Error::Code parse(bool &v, std::string_view new_value)
	{
		v = !v;
		return Error::Code::no_error;
	}
}
