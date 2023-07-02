#pragma once

#include "../BaseArguments.hpp"

namespace SCT::ArgsP::Arguments
{
	template<typename T>
	SCT_ArgsP_INL Base<T>::Base(const T& bs)
		: p_value(bs) {}

	template<typename T>
	SCT_ArgsP_INL Base<T>::~Base() {}

	template<typename T>
	SCT_ArgsP_INL const T& Base<T>::get() const noexcept
		{ return p_value; }
}
