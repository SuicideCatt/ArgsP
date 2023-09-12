#pragma once

#include "Base.hpp"

namespace SCT::ArgsP::Arguments
{
	template<typename Type>
	using ValueParsePtr = void(*)(Type&, const std::string_view&);

	template<typename _Type, ValueParsePtr<_Type> _ValueParsePtr = nullptr>
	class Base : public ArgsP::Base
	{
	public:
		using Type = _Type;

		SCT_ArgsP_INL Base(const Type& base_value = Type());
		virtual ~Base() = default;

		SCT_ArgsP_INL const Type& get() const noexcept;
		SCT_ArgsP_INL operator const Type&() const noexcept;
		SCT_ArgsP_INL const Type& operator*() const noexcept;

	protected:
		virtual bool parse(SCT_ArgsP_parse_parameters) override;
		virtual void parse_value(const std::string_view& new_value);

	 	Type p_value;
	};
}

#include "tpp/BaseArguments.hpp"
