#pragma once

#include "BaseArguments.hpp"
#include "Setters.hpp"

namespace SCT::ArgsP::Arguments
{
	using String = Base<std::string_view, &Setters::parse>;
	using Int64 = Base<int64_t, &Setters::parse>;
}
