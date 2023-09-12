#pragma once

#include "../Parser.hpp"

namespace SCT::ArgsP {
	SCT_ArgsP_INL Parser::Parser(const char& prefix): m_prefix(prefix) {}

	SCT_ArgsP_INL void Parser::add_argument(Base& arg)
		{ m_args.push_back(&arg); }

	SCT_ArgsP_INL const std::string_view Parser::parse(int argc, char* argv[])
	{
		parse_no_program({argv + 1, argv + argc});
		return *argv;
	}

	SCT_ArgsP_INL void Parser::parse_no_program(int argc, char* argv[])
		{ parse_no_program({argv, argv + argc}); }

	SCT_ArgsP_INL const std::string_view Parser::parse(const Argv& argv)
	{
		parse_no_program({argv.begin() + 1, argv.end()});
		return argv.front();
	}

	SCT_ArgsP_INL void Parser::parse_no_program(Argv argv)
	{
		auto end = argv.end();
		for (auto arg = argv.begin(); arg != end; ++arg)
		{
			for (auto m_arg = m_args.begin(); m_arg != m_args.end(); ++m_arg)
			{
				if ((*m_arg)->parse(arg, end, m_prefix))
				{
					m_args.erase(m_arg);
					break;
				}
			}
		}
	}

}
