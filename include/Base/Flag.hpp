#pragma once

#include "Parameter.hpp"

namespace SCT::ArgsP::Base
{
	template<ValueParsePtr<bool> parse_function>
	class Flag : public Argument<bool, parse_function>
	{
	public:
		using Info = ArgsP::Base::Info;
		using Infos = ArgsP::Base::Infos;

		SCT_ArgsP_INL
			Flag(Infos names, bool base_value = false);
		virtual ~Flag() override = default;

	protected:
		virtual bool parse(SCT_ArgsP_parse_parameters) override;

		std::vector<Info> p_names;
	};
}

#include "../tpp/Base/Flag.hpp"
