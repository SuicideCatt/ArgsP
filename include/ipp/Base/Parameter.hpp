#pragma once

#include "../../Base/Parameter.hpp"

namespace SCT::ArgsP::Base
{
	namespace DarkSide
	{
		void error(const char*);
	}

	SCT_ArgsP_INL consteval
		Info::Info(size_t prefix_count, std::string_view name)
		: prefix_count(prefix_count), name(name)
	{
		if (prefix_count < 1)
			DarkSide::error("Prefix count less 1");
		if (name.length() < 1)
			DarkSide::error("Name length less 1");
		if (name.find('=') != name.npos)
			DarkSide::error("'=' symbol detected in name");
	}
}
