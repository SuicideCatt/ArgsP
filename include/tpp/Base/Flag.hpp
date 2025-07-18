#pragma once

#include "../../Base/Flag.hpp"

namespace SCT::ArgsP::Base
{
	template<ValueParsePtr<bool> parse_function>
	SCT_ArgsP_INL Flag<parse_function>::Flag(Infos names, bool base_value)
		: Argument<bool, parse_function>(base_value), p_names(names) {}

	template<ValueParsePtr<bool> parse_function>
	inline bool Flag<parse_function>::parse(SCT_ArgsP_parse_parameters)
	{
		using namespace Error;

		for (auto& [pc, f] : p_names)
		{
			if (!DarkSide::check_prefix(pc, prefix, *iterator)) continue;

			auto offset = iterator->find('=');
			if (iterator->substr(pc, offset - pc) != f) continue;

			if (offset != std::string_view::npos)
			{
				const auto& str  = *iterator;
				auto arg = str.substr(0, offset);
				auto val = str.substr(offset + 1);

				error.set_error(Exception(std::string(arg), std::string(val),
										  Code::invalid_value));
				return false;
			}

			auto err = this->parse_value("");
			if (err != Code::no_error)
			{
				error.set_error(Exception(std::string(*iterator), "no value",
										  Code::invalid_value));
				return false;
			}

			return true;
		}

		return false;
	}
}
