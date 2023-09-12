#pragma once

#pragma once

#include "Defines.hpp"

#include <string>
#include <cstdint>

namespace SCT::ArgsP::Setters
{
	SCT_ArgsP_INL void
		parse(std::string_view& value, const std::string_view& new_value);
	SCT_ArgsP_INL void parse(bool& value, const std::string_view& new_value);

	template<int Base = 0>
	SCT_ArgsP_INL void parse(int64_t& value, const std::string_view& new_value);
}

#include "ipp/Setters.hpp"
#include "tpp/Setters.hpp"
