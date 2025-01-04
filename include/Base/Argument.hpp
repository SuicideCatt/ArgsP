#pragma once

#include "../Error.hpp"
#include "Base.hpp"

namespace SCT::ArgsP::Base
{
	template<typename Type>
	using ValueParsePtr = Error::Code(*)(Type&, std::string_view);

	template<typename _Type, ValueParsePtr<_Type> parse_function = nullptr>
	class Argument : public Base
	{
	public:
		using Type = _Type;

		SCT_ArgsP_INL Argument(const Type& base_value = Type());
		virtual ~Argument() override = default;

		SCT_ArgsP_INL const Type& get() const noexcept;
		SCT_ArgsP_INL operator const Type&() const noexcept;
		SCT_ArgsP_INL const Type& operator*() const noexcept;

	protected:
		virtual bool parse(SCT_ArgsP_parse_parameters) override;
		virtual Error::Code parse_value(std::string_view new_value);

	 	Type p_value;
	};
}

#include "../tpp/Base/Argument.hpp"
