#pragma once

#include "Defines.hpp"

#include <memory>
#include <source_location>
#include <system_error>
#include <variant>

namespace SCT::ArgsP::Error
{
	enum class Code : int
	{
		no_error,
		can_not_parse_program_argument,
		no_function_for_parse_value,
		no_value_provided,
		syntax_error,
		invalid_value,
		out_of_range,
	};

	struct Category : public std::error_category
	{
		SCT_ArgsP_INL const char* name() const noexcept override;
		SCT_ArgsP_INL std::string message(int errc) const override;
	};

	SCT_ArgsP_INL const Category& get_category();

	class Exception : public std::system_error
	{
	public:
		SCT_ArgsP_INL Exception(Code code,
					std::source_location src = std::source_location::current());
		SCT_ArgsP_INL Exception(std::string value, Code code,
					std::source_location src = std::source_location::current());
		SCT_ArgsP_INL Exception(std::string arg, std::string value, Code code,
					std::source_location src = std::source_location::current());

		const std::string argument, value;
		const std::source_location location;
	};
	
	SCT_ArgsP_INL std::error_code make_error_code(Error::Code code);
}

namespace SCT::ArgsP
{
	using Error::make_error_code;

	// Bad version of std::expected(C++23)
	template<typename _Result, typename _Error>
	class VariantResult : private std::variant<_Error, _Result>
	{
	public:
		using Result = _Result;
		using Error = _Error;

		SCT_ArgsP_INL VariantResult(const Result& value) noexcept;
		SCT_ArgsP_INL VariantResult(Error error) noexcept;

		VariantResult(const VariantResult&) = default;
		VariantResult& operator=(const VariantResult&) = default;

		VariantResult(VariantResult&&) = default;
		VariantResult& operator=(VariantResult&&) = default;

		SCT_ArgsP_INL bool has_value() const noexcept;
		SCT_ArgsP_INL operator bool() const noexcept;

		SCT_ArgsP_INL const Result&
			value_or(const Result& default_value = Result()) const noexcept;

		// Retunr 0 if no error
		SCT_ArgsP_INL Error error() const noexcept;

	private:
		using in_Result = const Result&;
		using Base = std::variant<_Error, _Result>;

		Base& to_parrent() noexcept;
		const Base& to_parrent() const noexcept;
	};

	template<typename _Exception>
	struct ExceptionContainer
	{
		using Exception = _Exception;

		virtual ~ExceptionContainer() = default;

		virtual void set_error(const Exception& exception);

		SCT_ArgsP_INL const Exception& get_error() const noexcept;

		SCT_ArgsP_INL bool error() const noexcept;

	private:
		std::unique_ptr<Exception> m_exception;
	};
}

namespace SCT::ArgsP::Error
{
	using Container = ExceptionContainer<Exception>;

	template<typename _Result>
	using Result = VariantResult<_Result, Code>;
}

namespace std
{
	template<>
	struct is_error_code_enum<SCT::ArgsP::Error::Code>
		: public true_type {};
}

#include "ipp/Error.hpp"
#include "tpp/Error.hpp"
