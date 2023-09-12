#pragma once

#include "../BaseFlags.hpp"

namespace SCT::ArgsP::Flags
{
	namespace DarkSide
	{
		void error(const char*);
	}

	SCT_ArgsP_INL consteval
		Info::Info(const size_t& pc, const std::string_view& n)
		: prefix_count(pc), name(n)
	{
		if (pc < 1)
			DarkSide::error("Soooory but yur prefix count less 1");
		if (n.length() < 1)
			DarkSide::error("flag name length less 1, why?");
		if (n.find('=') != n.npos)
			DarkSide::error("'=' symbol detected in flag ¯\\_(ツ)_/¯");
	}
}
