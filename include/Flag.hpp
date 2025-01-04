#pragma once

#include "Base/Flag.hpp"
#include "Setters.hpp"

namespace SCT::ArgsP::Flag
{
	template<Base::ValueParsePtr<bool> parse_function = nullptr>
	using Base = ArgsP::Base::Flag<parse_function>;

	using Bool = Base<&Setters::parse>;
}
