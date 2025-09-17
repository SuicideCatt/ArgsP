#pragma once

#include "../../Base/Argument.hpp"

namespace SCT::ArgsP::Base
{
	template<typename Type, ValueParsePtr<std::optional<Type>> parse_function>
	SCT_ArgsP_INL Argument<std::optional<Type>, parse_function>
		::Argument(OptType base_value)
		: p_value(base_value) {}

	template<typename Type, ValueParsePtr<std::optional<Type>> parse_function>
	SCT_ArgsP_INL auto Argument<std::optional<Type>, parse_function>::get() const noexcept
		-> const OptType&
		{ return p_value; }

	template<typename Type, ValueParsePtr<std::optional<Type>> parse_function>
	SCT_ArgsP_INL bool Argument<std::optional<Type>, parse_function>
		::has_value() const noexcept
		{ return p_value.has_value(); }

	template<typename Type, ValueParsePtr<std::optional<Type>> parse_function>
	SCT_ArgsP_INL Argument<std::optional<Type>, parse_function>
		::operator bool() const noexcept
		{ return p_value; }

	template<typename Type, ValueParsePtr<std::optional<Type>> parse_function>
	SCT_ArgsP_INL Type Argument<std::optional<Type>, parse_function>
		::value_or(Type&& default_value) const noexcept
		{ return p_value.value_or(std::forward<Type>(default_value)); }

	template<typename Type, ValueParsePtr<std::optional<Type>> parse_function>
	SCT_ArgsP_INL const Type& Argument<std::optional<Type>, parse_function>
		::operator*()
		{ return p_value.value(); }

	template<typename Type, ValueParsePtr<std::optional<Type>> parse_function>
	SCT_ArgsP_INL const Type& Argument<std::optional<Type>, parse_function>
		::value()
		{ return p_value.value(); }

	template<typename Type, ValueParsePtr<std::optional<Type>> parse_function>
	bool Argument<std::optional<Type>, parse_function>::parse(SCT_ArgsP_parse_parameters)
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

	template<typename Type, ValueParsePtr<std::optional<Type>> parse_function>
	SCT_ArgsP_INL Error::Code Argument<std::optional<Type>, parse_function>
		::parse_value(std::string_view new_value)
	{
		if constexpr (parse_function == nullptr)
			return Error::Code::no_function_for_parse_value;
		else
			return parse_function(this->p_value, new_value);
	}

	template<ValueParsePtr<bool> parse_function>
	SCT_ArgsP_INL Argument<bool, parse_function>::Argument(bool base_value)
		: p_value(base_value) {}

	template<ValueParsePtr<bool> parse_function>
	SCT_ArgsP_INL bool Argument<bool, parse_function>::get() const noexcept
		{ return p_value; }

	template<ValueParsePtr<bool> parse_function>
	SCT_ArgsP_INL Argument<bool, parse_function>::operator bool() const noexcept
		{ return p_value; }

	template<ValueParsePtr<bool> parse_function>
	SCT_ArgsP_INL bool Argument<bool, parse_function>::operator*() const noexcept
		{ return p_value; }

	template<ValueParsePtr<bool> parse_function>
	SCT_ArgsP_INL bool Argument<bool, parse_function>::value() const noexcept
		{ return p_value; }

	template<ValueParsePtr<bool> parse_function>
	bool Argument<bool, parse_function>::parse(SCT_ArgsP_parse_parameters)
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

	template<ValueParsePtr<bool> parse_function>
	SCT_ArgsP_INL Error::Code
		Argument<bool, parse_function>::parse_value(std::string_view new_value)
	{
		if constexpr (parse_function == nullptr)
			return Error::Code::no_function_for_parse_value;
		else
			return parse_function(this->p_value, new_value);
	}
}
