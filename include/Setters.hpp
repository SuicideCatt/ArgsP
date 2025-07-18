#pragma once

#pragma once

#include "StringTo.hpp"
#include "Defines.hpp"

#include <string_view>
#include <cstdint>

namespace SCT::ArgsP::Setters
{
	enum class IntBase : int
	{
		automatic = 0, bin = 2, dec = 10, hex = 16
	};

	SCT_ArgsP_INL
		Error::Code parse(std::string_view& value, std::string_view new_value);
	SCT_ArgsP_INL Error::Code parse(bool& value, std::string_view new_value);

	template<std::integral Type, IntBase base = IntBase::automatic>
	SCT_ArgsP_INL Error::Code parse(Type& value, std::string_view new_value);

	template<std::floating_point Type>
	SCT_ArgsP_INL Error::Code parse(Type& value, std::string_view new_value);
}

#include "ipp/Setters.hpp"
#include "tpp/Setters.hpp"
