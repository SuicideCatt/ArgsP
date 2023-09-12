#pragma once

#include "../Parser.hpp"

namespace SCT::ArgsP
{
	namespace DarkSide
	{
		SCT_ArgsP_INL void parser_add_arguments(Parser& parser) {}

		template<IsArgument First, IsArgument... Args>
		SCT_ArgsP_INL void
			parser_add_arguments(Parser& parser, First& arg, Args&... args)
		{
			parser.add_argument(arg);
			parser_add_arguments(parser, args...);
		}
	}

	template<IsArgument... Args>
	SCT_ArgsP_INL void Parser::add_arguments(Args&... args)
		{ DarkSide::parser_add_arguments(*this, args...); }
}
