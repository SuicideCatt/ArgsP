#pragma once

#include "BaseArguments.hpp"

namespace SCT::ArgsP::Flags
{
	struct Info
	{
		SCT_ArgsP_INL consteval
			Info(const size_t& prefix_count, const std::string_view& name);

		size_t prefix_count = 0;
		std::string_view name = "";
	};

	using Infos = std::initializer_list<Info>;

	template<typename Type,
			 Arguments::ValueParsePtr<Type> _ValueParsePtr = nullptr>
	class Base : public Arguments::Base<Type, _ValueParsePtr>
	{
	public:
		SCT_ArgsP_INL
			Base(const Infos& flags, const Type& base_value = Type());
		virtual ~Base() = default;

	protected:
		virtual bool parse(SCT_ArgsP_parse_parameters) override;

		std::vector<Info> p_flags;
	};

	template<Arguments::ValueParsePtr<bool> _ValueParsePtr>
	class Base<bool, _ValueParsePtr>
		: public Arguments::Base<bool, _ValueParsePtr>
	{
	public:
		SCT_ArgsP_INL
			Base(const Infos& flags, const bool& base_value = false);
		virtual ~Base() = default;

	protected:
		virtual bool parse(SCT_ArgsP_parse_parameters) override;

		std::vector<Info> p_flags;
	};
}

#include "ipp/BaseFlags.hpp"
#include "tpp/BaseFlags.hpp"
