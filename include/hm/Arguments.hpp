#pragma once

#include "../Arguments.hpp"

namespace SCT::ArgsP::Arguments
{
	SCT_ArgsP_HM
	String::String(std::string_view bv) : Base(bv) {};
	SCT_ArgsP_HM
	String::~String() {};

	SCT_ArgsP_HM
	bool String::parse(Argv::iterator& itr, Argv::const_iterator end,
					   const char& p)
	{
		if ((*itr)[0] != p)
		{
			p_value = *itr;
			return true;
		}

		return false;
	}

	SCT_ArgsP_HM
	Int64::Int64(int64_t bv, int b) : Base(bv), m_base(b) {};
	SCT_ArgsP_HM
	Int64::~Int64() {};

	SCT_ArgsP_HM
	bool Int64::parse(Argv::iterator& itr, Argv::const_iterator end,
					   const char& p)
	{
		if ((*itr)[0] != p)
		{
			p_value = std::stoll(std::string(*itr), nullptr, m_base);
			return true;
		}

		return false;
	}
}
