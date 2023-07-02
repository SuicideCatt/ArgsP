#pragma once

#include "../BaseFlags.hpp"

namespace SCT::ArgsP::Flags
{
	template<typename T>
	SCT_ArgsP_INL Base<T>::Base(const Infos& fs, const T& bs)
		: Arguments::Base<T>(bs), p_flags(fs) {}

	template<typename T>
	SCT_ArgsP_INL Base<T>::~Base() {}
}
