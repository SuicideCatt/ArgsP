#pragma once

#include "../Parser.hpp"

namespace SCT::ArgsP
{
	namespace DarkSide
	{
		template<IsArgumentSPtr Last>
		SCT_ArgsP_INL void parser_add_arguments(Parser& parser, Last&& arg)
			{ parser.add_argument(std::forward<Last>(arg)); }

		template<IsArgumentSPtr First, typename... Args>
		SCT_ArgsP_INL
		void parser_add_arguments(Parser& parser, First&& arg, Args&&... args)
		{
			parser.add_argument(std::forward<First>(arg));
			parser_add_arguments(parser, std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	SCT_ArgsP_INL void Parser::add_arguments(Args&&... args)
		{ DarkSide::parser_add_arguments(*this, std::forward<Args>(args)...); }
}
