#pragma once

#include "../Error.hpp"
#include "Base.hpp"

#include <optional>

namespace SCT::ArgsP::Base
{
	template<typename Type>
	using ValueParsePtr = Error::Code(*)(Type&, std::string_view);

	template<typename _Type, ValueParsePtr<_Type> parse_function = nullptr>
	class Argument;

	template<typename _Type, ValueParsePtr<std::optional<_Type>> parse_function>
	class Argument<std::optional<_Type>, parse_function> : public Base
	{
	public:
		using Type = _Type;
		using OptType = std::optional<Type>;

		SCT_ArgsP_INL Argument(OptType base_value = std::nullopt);
		virtual ~Argument() override = default;

		SCT_ArgsP_INL const OptType& get() const noexcept;

		SCT_ArgsP_INL bool has_value() const noexcept;
		SCT_ArgsP_INL operator bool() const noexcept;

		SCT_ArgsP_INL Type value_or(Type&& default_value) const noexcept;

		SCT_ArgsP_INL const Type& operator*();
		SCT_ArgsP_INL const Type& value();

	protected:
		virtual bool parse(SCT_ArgsP_parse_parameters) override;
		virtual Error::Code parse_value(std::string_view new_value);

		OptType p_value;
	};

	template<ValueParsePtr<bool> parse_function>
	class Argument<bool, parse_function> : public Base
	{
	public:
		using Type = bool;

		SCT_ArgsP_INL Argument(bool base_value = false);
		virtual ~Argument() override = default;

		SCT_ArgsP_INL bool get() const noexcept;
		SCT_ArgsP_INL operator bool() const noexcept;
		SCT_ArgsP_INL bool operator*() const noexcept;
		SCT_ArgsP_INL bool value() const noexcept;

	protected:
		virtual bool parse(SCT_ArgsP_parse_parameters) override;
		virtual Error::Code parse_value(std::string_view new_value);

	 	bool p_value;
	};
}

#include "../tpp/Base/Argument.hpp"
