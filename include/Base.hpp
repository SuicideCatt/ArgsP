#pragma once

#include "Defines.hpp"

#include <memory>
#include <string_view>
#include <vector>

namespace SCT::ArgsP
{
	using Argv = std::vector<std::string_view>;

	struct Base
	{
		using SPtr = std::shared_ptr<Base>;

		SCT_ArgsP_INL Base();
		SCT_ArgsP_INL virtual ~Base();

		SCT_ArgsP_HM
		virtual bool parse(Argv::iterator& iterator, Argv::const_iterator end,
						   const char& prefix) = 0;
	};

	template<typename Type>
	concept IsArgument =
		std::derived_from<std::remove_reference_t<Type>, Base>;

	template<typename Type>
	concept IsArgumentSPtr =
		IsArgument<typename std::remove_reference_t<Type>::element_type>;
}

#include "ipp/BaseArgument.hpp"
