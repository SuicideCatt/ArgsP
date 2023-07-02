#pragma once

#include "Defines.hpp"

#include "Base.hpp"

#include <list>
#include <string_view>

namespace SCT::ArgsP
{
	class Parser final
	{
	public:
		SCT_ArgsP_HM
		Parser(const char& prefix);

		SCT_ArgsP_HM
		void add_argument(Base::SPtr argument);

		template<typename... Args>
		SCT_ArgsP_INL void add_arguments(Args&&... args);

		SCT_ArgsP_HM
		const std::string_view parse(int argc, char* argv[]);
		SCT_ArgsP_HM
		void parse_no_program(int argc, char* argv[]);

		SCT_ArgsP_HM
		const std::string_view parse(const Argv& argv);
		SCT_ArgsP_HM
		void parse_no_program(Argv argv);

	private:
		std::list<Base::SPtr> m_args;
		char m_prefix;
	};
}

#include "tpp/Parser.hpp"

#ifdef USE_SCT_ArgsP_HM
	#include "hm/Parser.hpp"
#endif
