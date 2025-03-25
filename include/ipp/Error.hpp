#pragma once

#include "../Error.hpp"

namespace SCT::ArgsP::Error
{
	SCT_ArgsP_INL const char* Category::name() const noexcept
		{ return "SCT::ArgsP"; }

	SCT_ArgsP_INL std::string Category::message(int errc) const
	{
		switch (static_cast<Code>(errc))
		{
		case Code::no_error:
			return "No error";
		case Code::can_not_parse_program_argument:
			return "Can't parse program argument";
		case Code::no_function_for_parse_value:
			return "No function for parse value";
		case Code::no_value_provided:
			return "No value provided";
		case Code::syntax_error:
			return "Syntax error";
		case Code::invalid_value:
			return "Invalid value";
		case Code::out_of_range:
			return "Out of range";

		default:
			return "Unknown error code (" + std::to_string(errc) + ')';
		};
	}

	SCT_ArgsP_INL std::error_condition
		Category::default_error_condition(int errc) const noexcept
		{ return std::error_condition(errc, *this); }

	SCT_ArgsP_INL const Category& get_category()
	{
		static Category instance;
		return instance;
	}

	SCT_ArgsP_INL Exception::Exception(Code code, std::source_location src)
		: system_error(make_error_code(code)), location(src) {}

	SCT_ArgsP_INL Exception::Exception(std::string value, Code code,
									   std::source_location src)
		: system_error(make_error_code(code), '\'' + value + '\''),
		  value(std::move(value)), location(src) {}

	SCT_ArgsP_INL Exception::Exception(std::string arg, std::string value,
									   Code code, std::source_location src)
		: system_error(make_error_code(code), arg + "='" + value + '\''),
		  argument(std::move(arg)), value(std::move(value)), location(src) {}
	
	SCT_ArgsP_INL std::error_code make_error_code(Error::Code code)
		{ return {static_cast<int>(code), Error::get_category()}; }
}
