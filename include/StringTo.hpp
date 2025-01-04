#pragma once

#include "Error.hpp"

#include <string>

namespace SCT::ArgsP
{
	template<std::integral Int>
	SCT_ArgsP_INL Error::Result<Int>
		str_to(std::string_view str, size_t* index = nullptr,
			   int base = 10) noexcept;

	template<>
	SCT_ArgsP_INL Error::Result<bool>
		str_to<bool>(std::string_view str, size_t* index,
					 int base) noexcept = delete;

	template<std::floating_point Float>
	SCT_ArgsP_INL Error::Result<Float>
		str_to(std::string_view str, size_t* index = nullptr) noexcept;
}

#include "tpp/StringTo.hpp"
