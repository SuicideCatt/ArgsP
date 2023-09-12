#pragma once

#include "../BaseArguments.hpp"

namespace SCT::ArgsP::Arguments::DarkSide
{
	void error(const char*);
}

namespace SCT::ArgsP::Arguments
{
	template<typename T, ValueParsePtr<T> VS>
	SCT_ArgsP_INL Base<T, VS>::Base(const T& bs)
		: p_value(bs) {}

	template<typename T, ValueParsePtr<T> VS>
	SCT_ArgsP_INL const T& Base<T, VS>::get() const noexcept
		{ return p_value; }

	template<typename T, ValueParsePtr<T> VS>
	SCT_ArgsP_INL Base<T, VS>::operator const T&() const noexcept
		{ return p_value; }

	template<typename T, ValueParsePtr<T> VS>
	SCT_ArgsP_INL const T& Base<T, VS>::operator*() const noexcept
		{ return p_value; }

	template<typename T, ValueParsePtr<T> VS>
	bool Base<T, VS>::parse(SCT_ArgsP_parse_parameters)
	{
		auto& value = *iterator;
		if ((*iterator)[0] != prefix)
		{
			parse_value(value);
			return true;
		}

		return false;
	}

	template<typename T, ValueParsePtr<T> VS>
	SCT_ArgsP_INL void Base<T, VS>::parse_value(const std::string_view& nv)
	{
		if constexpr (VS == nullptr)
			DarkSide::error("Please create new child class for override "
							"Base::parse_value(...) method, "
							"or create function and get pointer");
		else
			VS(this->p_value, nv);
	}
}
