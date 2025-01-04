#pragma once

#include "Base/Base.hpp"
#include "Error.hpp"

#include <list>
#include <optional>

namespace SCT::ArgsP
{
	class Parser final
	{
	public:
		SCT_ArgsP_INL Parser(char prefix, bool throw_error = true);

		SCT_ArgsP_INL void add_argument(Base::Base& argument);

		template<IsArgument... Args>
		SCT_ArgsP_INL void add_arguments(Args&... args);

		SCT_ArgsP_INL
			std::optional<std::string_view> parse(int argc, char* argv[]);
		SCT_ArgsP_INL bool parse_no_program(int argc, char* argv[]);

		SCT_ArgsP_INL std::optional<std::string_view> parse(const ArgV& argv);
		SCT_ArgsP_INL bool parse_no_program(const ArgV& argv);

		SCT_ArgsP_INL bool error() const noexcept;
		SCT_ArgsP_INL
			const Error::Container& get_error_container() const noexcept;

	private:
		using Itr = ArgV::const_iterator;
		SCT_ArgsP_INL bool parse_no_program_impl(Itr arg, Itr end);

		char m_prefix;
		std::unique_ptr<Error::Container> m_error;
		std::list<Base::Base*> m_args;
	};
}

#include "ipp/Parser.hpp"
#include "tpp/Parser.hpp"
