#pragma once

#include "BaseFlags.hpp"
#include "Setters.hpp"

namespace SCT::ArgsP::Flags
{
	using String = Base<std::string_view, &Setters::parse>;
	using Int64 = Base<int64_t, &Setters::parse>;
	using Bool = Base<bool, &Setters::parse>;
}
