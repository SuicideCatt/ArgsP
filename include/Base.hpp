#pragma once

#include "Defines.hpp"

#include <string_view>
#include <vector>

#define SCT_ArgsP_parse_parameters \
	Argv::iterator& iterator, const Argv::iterator& end, const char& prefix

namespace SCT::ArgsP
{
	using Argv = std::vector<std::string_view>;

	struct Base
	{
		Base() = default;
		virtual ~Base() = default;

		virtual bool parse(SCT_ArgsP_parse_parameters) = 0;
	};

	template<typename Type>
	concept IsArgument =
		std::derived_from<std::remove_reference_t<Type>, Base>;
}
