#pragma once

#include "../Parser.hpp"

namespace SCT::ArgsP
{
	template<IsArgument... Args>
	SCT_ArgsP_INL void Parser::add_arguments(Args&... args)
	{
		std::initializer_list<Base::Base*> args_il = {&args...};
		m_args.insert(m_args.end(), args_il.begin(), args_il.end());
	}
}
