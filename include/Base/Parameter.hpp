#pragma once

#include "Argument.hpp"

namespace SCT::ArgsP::Base
{
	struct Info
	{
		SCT_ArgsP_INL consteval
			Info(size_t prefix_count, std::string_view name);

		size_t prefix_count = 0;
		std::string_view name = "";
	};

	using Infos = std::initializer_list<Info>;

	template<typename Type, ValueParsePtr<Type> parse_function = nullptr>
	class Parameter : public Argument<Type, parse_function>
	{
	public:
		using Info = ArgsP::Base::Info;
		using Infos = ArgsP::Base::Infos;

		SCT_ArgsP_INL
			Parameter(Infos names, const Type& base_value = Type());
		virtual ~Parameter() override = default;

	protected:
		virtual bool parse(SCT_ArgsP_parse_parameters) override;

		std::vector<Info> p_names;
	};
}

#include "../ipp/Base/Parameter.hpp"
#include "../tpp/Base/Parameter.hpp"
