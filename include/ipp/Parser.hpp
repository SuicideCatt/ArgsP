#pragma once

#include "../Parser.hpp"

namespace SCT::ArgsP
{
	SCT_ArgsP_INL Parser::Parser(char prefix, bool throw_error)
		: m_prefix(prefix)
	{
#ifdef __cpp_exceptions
		if (throw_error)
		{
			struct Thrower : Error::Container
			{
				void set_error(const Exception& exception) override
				{
					Error::Container::set_error(exception);
					throw get_error();
				}
			};

			m_error.reset(new Thrower());
		}
		else
#endif
		{
			m_error.reset(new Error::Container());
		}
	}

	SCT_ArgsP_INL void Parser::add_argument(Base::Base& arg)
		{ m_args.push_back(&arg); }

	SCT_ArgsP_INL
		std::optional<std::string_view> Parser::parse(int argc, char* argv[])
	{
		if (parse_no_program({argv + 1, argv + argc}))
			return *argv;
		else
			return std::nullopt;
	}

	SCT_ArgsP_INL bool Parser::parse_no_program(int argc, char* argv[])
		{ return parse_no_program({argv, argv + argc}); }

	SCT_ArgsP_INL
		std::optional<std::string_view> Parser::parse(const ArgV& argv)
	{
		if (parse_no_program_impl(argv.cbegin() + 1, argv.cend()))
			return argv.front();
		else
			return std::nullopt;
	}

	SCT_ArgsP_INL bool Parser::parse_no_program(const ArgV& argv)
		{ return parse_no_program_impl(argv.cbegin(), argv.cend()); }

	SCT_ArgsP_INL bool Parser::parse_no_program_impl(Itr arg, Itr end)
	{
		for (; arg != end; ++arg)
		{
			for (auto m_arg = m_args.begin(); m_arg != m_args.end(); ++m_arg)
			{
				if ((*m_arg)->parse(arg, end, m_prefix, *m_error))
				{
					m_args.erase(m_arg);
					break;
				}

				if (error())
					return false;
			}
		}

		return true;
	}

	SCT_ArgsP_INL bool Parser::error() const noexcept
		{ return m_error->error(); }

	SCT_ArgsP_INL
		const Error::Container& Parser::get_error_container() const noexcept
		{ return *m_error; }
}
