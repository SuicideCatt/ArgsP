#pragma once

#include "../BaseFlags.hpp"

#include <stdexcept>
#include <string>

namespace SCT::ArgsP::Flags::DarkSide
{
	SCT_ArgsP_INL bool
		check_prefix(const size_t& c, const char& p, std::string_view t)
	{
		t = t.substr(0, c);
		std::string ps(c, p);
		return t == ps;
	}
}

namespace SCT::ArgsP::Flags
{
	template<typename T, Arguments::ValueParsePtr<T> VS>
	SCT_ArgsP_INL Base<T, VS>::Base(const Infos& fs, const T& bs)
		: Arguments::Base<T, VS>(bs), p_flags(fs) {}

	template<typename T, Arguments::ValueParsePtr<T> VS>
	bool Base<T, VS>::parse(SCT_ArgsP_parse_parameters)
	{
		for (auto& [pc, f] : p_flags)
		{
			if (!DarkSide::check_prefix(pc, prefix, *iterator)) continue;

			auto offset = iterator->find('=');
			if (iterator->substr(pc, offset - pc) != f) continue;

			if (offset == std::string_view::npos)
			{
				if (++iterator != end)
				{
					this->parse_value(*iterator);
					return true;
				}
				throw std::runtime_error("SCT::ArgsP::Flags::Base::parse(...) "
										 "No value provided");
			}
			else
			{
				this->parse_value(iterator->substr(offset + 1));
				return true;
			}
		}

		return false;
	}

	template<Arguments::ValueParsePtr<bool> VS>
	SCT_ArgsP_INL Base<bool, VS>::Base(const Infos& fs, const bool& bs)
		: Arguments::Base<bool, VS>(bs), p_flags(fs) {}

	template<Arguments::ValueParsePtr<bool> VS>
	inline bool Base<bool, VS>::parse(SCT_ArgsP_parse_parameters)
	{
		for (auto& [pc, f] : p_flags)
		{
			if (!DarkSide::check_prefix(pc, prefix, *iterator)) continue;
			if (iterator->substr(pc) != f) continue;

			this->parse_value("");

			return true;
		}

		return false;
	}
}
