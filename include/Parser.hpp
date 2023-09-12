#pragma once

#include "Base.hpp"

#include <list>

namespace SCT::ArgsP
{
	class Parser final
	{
	public:
		SCT_ArgsP_INL Parser(const char& prefix);

		SCT_ArgsP_INL void add_argument(Base& argument);

		template<IsArgument... Args>
		SCT_ArgsP_INL void add_arguments(Args&... args);

		SCT_ArgsP_INL const std::string_view parse(int argc, char* argv[]);
		SCT_ArgsP_INL void parse_no_program(int argc, char* argv[]);

		SCT_ArgsP_INL const std::string_view parse(const Argv& argv);
		SCT_ArgsP_INL void parse_no_program(Argv argv);

	private:
		std::list<Base*> m_args;
		char m_prefix;
	};
}

#include "ipp/Parser.hpp"
#include "tpp/Parser.hpp"
