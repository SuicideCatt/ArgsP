#pragma once

#include "Defines.hpp"

#include "BaseFlags.hpp"

namespace SCT::ArgsP::Flags
{
	class String final : public Base<std::string_view>
	{
	public:
		SCT_ArgsP_HM
		String(Infos flags, std::string_view base_value = "");
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
		Int64(Infos flags, int64_t base_value = 0, int base = 10);
		SCT_ArgsP_HM
		~Int64();

	private:
		SCT_ArgsP_HM
		bool parse(Argv::iterator& iterator, Argv::const_iterator end,
				   const char& prefix) override;

		int m_base;
	};

	class Bool final : public Base<bool>
	{
	public:
		SCT_ArgsP_HM
		Bool(Infos flags, bool base_value = false);
		SCT_ArgsP_HM
		~Bool();

	private:
		SCT_ArgsP_HM
		bool parse(Argv::iterator& iterator, Argv::const_iterator end,
				   const char& prefix) override;
	};
}

#ifdef USE_SCT_ArgsP_HM
	#include "hm/Flags.hpp"
#endif
