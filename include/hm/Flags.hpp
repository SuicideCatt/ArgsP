#pragma once

#include "../Flags.hpp"

namespace SCT::ArgsP::Flags
{
	namespace DarkSide
	{
		SCT_ArgsP_INL
		bool check_prefix(size_t c, const char& p, std::string_view t)
		{
			t = t.substr(0, c);
			std::string ps(c, p);
			return t == ps;
		}

		template<typename T, typename FuncType>
		SCT_ArgsP_INL
		bool parse(Argv::iterator& itr, Argv::const_iterator end, const char& p,
				   const std::vector<Info>& fs, T& value, const FuncType& func)
		{
			for (auto& [pc, f] : fs)
			{
				if (!DarkSide::check_prefix(pc, p, *itr)) continue;

				auto s = itr->find('=');
				if (itr->substr(pc, s - pc) != f) continue;

				func(itr, end, s, value);

				return true;
			}

			return false;
		}
	}

	SCT_ArgsP_HM
	String::String(Infos fs, std::string_view bv) : Base(fs, bv) {}
	SCT_ArgsP_HM
	String::~String() {}

	SCT_ArgsP_HM
	bool String::parse(Argv::iterator& itr, Argv::const_iterator end,
					   const char& p)
	{
		return DarkSide::parse(itr, end, p, p_flags, p_value,
			[](Argv::iterator& itr, Argv::const_iterator end,
			   size_t s, std::string_view& value)
			{
				if (s == value.npos) [[unlikely]]
				{
					if (++itr != end) value = *itr;
					else throw std::runtime_error("No value provided");
				}
				else [[likely]]
				{
					value = itr->substr(s + 1);
				}
			});
	}

	SCT_ArgsP_HM
	Int64::Int64(Infos fs, int64_t bv, int b) : Base(fs, bv), m_base(b) {}
	SCT_ArgsP_HM
	Int64::~Int64() {}

	SCT_ArgsP_HM
	bool Int64::parse(Argv::iterator& itr, Argv::const_iterator end,
					   const char& p)
	{
		return DarkSide::parse(itr, end, p, p_flags, p_value,
			[base=m_base](Argv::iterator& itr, Argv::const_iterator end,
			   size_t s, int64_t& value)
			{
				if (s == std::string_view::npos) [[unlikely]]
				{
					if (++itr != end)
						value = std::stoll(std::string(*itr), nullptr, base);
					else throw std::runtime_error("No value provided");
				}
				else [[likely]]
				{
					value = std::stoll(std::string(itr->substr(s + 1)),
									   nullptr, base);
				}
			});
	}

	SCT_ArgsP_HM
	Bool::Bool(Infos fs, bool bv) : Base(fs, bv) {}
	SCT_ArgsP_HM
	Bool::~Bool() {}

	SCT_ArgsP_HM
	bool Bool::parse(Argv::iterator& itr, Argv::const_iterator end,
					   const char& p)
	{
		for (auto& [pc, f] : p_flags)
		{
			if (!DarkSide::check_prefix(pc, p, *itr)) continue;
			if (itr->substr(pc) != f) continue;

			p_value = !p_value;

			return true;
		}

		return false;
	}

}
