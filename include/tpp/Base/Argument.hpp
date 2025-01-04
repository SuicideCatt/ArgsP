#pragma once

#include "../../Base/Argument.hpp"

namespace SCT::ArgsP::Base
{
	template<typename T, ValueParsePtr<T> parse_function>
	SCT_ArgsP_INL Argument<T, parse_function>::Argument(const T& base_value)
		: p_value(base_value) {}

	template<typename T, ValueParsePtr<T> parse_function>
	SCT_ArgsP_INL const T& Argument<T, parse_function>::get() const noexcept
		{ return p_value; }

	template<typename T, ValueParsePtr<T> parse_function>
	SCT_ArgsP_INL
		Argument<T, parse_function>::operator const T&() const noexcept
		{ return get(); }

	template<typename T, ValueParsePtr<T> parse_function>
	SCT_ArgsP_INL
		const T& Argument<T, parse_function>::operator*() const noexcept
		{ return get(); }

	template<typename T, ValueParsePtr<T> parse_function>
	bool Argument<T, parse_function>::parse(SCT_ArgsP_parse_parameters)
	{
		using namespace Error;

		const auto& value = *iterator;
		if ((*iterator)[0] != prefix)
		{
			auto err = parse_value(value);
			if (err == Code::no_error)
				return true;

			error.set_error(Exception(std::string(value), err));
		}

		return false;
	}

	template<typename T, ValueParsePtr<T> parse_function>
	SCT_ArgsP_INL Error::Code
		Argument<T, parse_function>::parse_value(std::string_view new_value)
	{
		if constexpr (parse_function == nullptr)
			return Error::Code::no_function_for_parse_value;
		else
			return parse_function(this->p_value, new_value);
	}
}
