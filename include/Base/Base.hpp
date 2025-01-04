#pragma once

#include "../ArgV.hpp"
#include "../Defines.hpp"
#include "../Error.hpp"

#define SCT_ArgsP_parse_parameters \
	SCT::ArgsP::ArgV::const_iterator& iterator, \
	const SCT::ArgsP::ArgV::const_iterator end, \
	char prefix, SCT::ArgsP::Error::Container& error

namespace SCT::ArgsP::Base
{
	struct Base
	{
		Base() = default;
		virtual ~Base() = default;

		virtual bool parse(SCT_ArgsP_parse_parameters) = 0;
	};
}

namespace SCT::ArgsP
{
	template<typename Type>
	concept IsArgument =
		std::derived_from<std::remove_reference_t<Type>, Base::Base>;
}
