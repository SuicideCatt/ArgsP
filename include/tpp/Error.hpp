#pragma once

#include "../Error.hpp"

namespace SCT::ArgsP
{
	template<typename Result, typename Error>
	SCT_ArgsP_INL
		VariantResult<Result, Error>::VariantResult(const Result& value) noexcept
		: std::variant<Error, Result>(value) {}

	template<typename Result, typename Error>
	SCT_ArgsP_INL
		VariantResult<Result, Error>::VariantResult(Error error) noexcept
		: std::variant<Error, Result>(error) {}

	template<typename Result, typename Error>
	SCT_ArgsP_INL bool VariantResult<Result, Error>::has_value() const noexcept
		{ return this->index(); }

	template<typename Result, typename Error>
	SCT_ArgsP_INL VariantResult<Result, Error>::operator bool() const noexcept
		{ return has_value(); }

	template<typename Result, typename Error>
	SCT_ArgsP_INL Result VariantResult<Result, Error>
		::value_or(Result&& default_value) const noexcept
		{ return has_value()? std::get<1>(to_parrent()) : default_value; }

	template<typename Result, typename Error>
	SCT_ArgsP_INL Error VariantResult<Result, Error>::error() const noexcept
		{ return !has_value()? std::get<0>(to_parrent()) : Error(); }

	template<typename Result, typename Error>
	SCT_ArgsP_INL VariantResult<Result, Error>::Base&
		VariantResult<Result, Error>::to_parrent() noexcept
		{ return static_cast<Base&>(*this); }

	template<typename Result, typename Error>
	SCT_ArgsP_INL const VariantResult<Result, Error>::Base&
		VariantResult<Result, Error>::to_parrent() const noexcept
		{ return static_cast<const Base&>(*this); }

	template<typename Exception>
	SCT_ArgsP_INL void
		ExceptionContainer<Exception>::set_error(const Exception& exception)
		{ m_exception.reset(new Exception(exception)); }

	template<typename Exception>
	SCT_ArgsP_INL const Exception&
		ExceptionContainer<Exception>::get_error() const noexcept
		{ return *m_exception; }

	template<typename Exception>
	SCT_ArgsP_INL bool ExceptionContainer<Exception>::error() const noexcept
		{ return static_cast<bool>(m_exception); }
}
