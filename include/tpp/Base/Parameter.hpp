#pragma once

#include "../../Base/Parameter.hpp"

namespace SCT::ArgsP::Base::DarkSide
{
	SCT_ArgsP_INL bool
		check_prefix(size_t c, char p, std::string_view t)
	{
		if (t.size() <= c)
			return false;

		t = t.substr(0, c);
		return t.find_last_not_of(p) == t.npos;
	}
}

namespace SCT::ArgsP::Base
{
	template<typename T, ValueParsePtr<T> parse_function>
	SCT_ArgsP_INL Parameter<T, parse_function>::Parameter(Infos names,
														  const T& base_value)
		: Argument<T, parse_function>(base_value), p_names(names) {}

	template<typename T, ValueParsePtr<T> parse_function>
	bool Parameter<T, parse_function>::parse(SCT_ArgsP_parse_parameters)
	{
		using namespace Error;

		auto pv = [this, &error](std::string_view arg, std::string_view value)
		{
			Code err = this->parse_value(value);
			if (err == Code::no_error)
				return true;

			error.set_error(Exception(std::string(arg),
									  std::string(value), err));
			return false;
		};

		for (auto& [pl, f] : p_names)
		{
			if (!DarkSide::check_prefix(pl, prefix, *iterator)) continue;

			auto offset = iterator->find('=');
			if (iterator->substr(pl, offset - pl) != f) continue;

			if (offset == std::string_view::npos)
			{
				if (++iterator != end)
					return pv(*(iterator-1), *iterator);

				error.set_error(Exception(std::string(*(iterator-1)),
										  "no value", Code::no_value_provided));
				return false;
			}
			else
			{
				return pv(iterator->substr(0, offset),
						  iterator->substr(offset + 1));
			}
		}

		return false;
	}
}
