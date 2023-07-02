#pragma once

#include "Defines.hpp"

#include "BaseArguments.hpp"

namespace SCT::ArgsP::Arguments
{
	class String final : public Base<std::string_view>
	{
	public:
		SCT_ArgsP_HM
		String(std::string_view base_value = "");
		SCT_ArgsP_HM
		~String();

	private:
		SCT_ArgsP_HM
		bool parse(Argv::iterator& iterator, Argv::const_iterator end,
				   const char& prefix) override;
	};

	class Int64 final : public Base<int64_t>
	{
	public:
		SCT_ArgsP_HM
		Int64(int64_t base_value = 0, int base = 10);
		SCT_ArgsP_HM
		~Int64();

	private:
		SCT_ArgsP_HM
		bool parse(Argv::iterator& iterator, Argv::const_iterator end,
				   const char& prefix) override;

		int m_base;
	};
}

#ifdef USE_SCT_ArgsP_HM
	#include "hm/Arguments.hpp"
#endif
