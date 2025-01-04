#pragma once

#include "../Error.hpp"

namespace SCT::ArgsP
{
	template<typename _Result, typename _Error>
	SCT_ArgsP_INL
		VariantResult<_Result, _Error>::VariantResult(in_Result value) noexcept
		: std::variant<_Error, _Result>(value) {}

	template<typename _Result, typename _Error>
	SCT_ArgsP_INL
		VariantResult<_Result, _Error>::VariantResult(Error error) noexcept
		: std::variant<_Error, _Result>(error) {}

	template<typename _Result, typename _Error>
	SCT_ArgsP_INL bool
		VariantResult<_Result, _Error>::has_value() const noexcept
		{ return this->index(); }

	template<typename _Result, typename _Error>
	SCT_ArgsP_INL VariantResult<_Result, _Error>::operator bool() const noexcept
		{ return has_value(); }

	template<typename _Result, typename _Error>
	SCT_ArgsP_INL const _Result&
		VariantResult<_Result, _Error>::value_or(in_Result default_value)
																const noexcept
		{ return has_value()? std::get<1>(to_parrent()) : default_value; }

	template<typename _Result, typename _Error>
	SCT_ArgsP_INL _Error VariantResult<_Result, _Error>::error() const noexcept
		{ return !has_value()? std::get<0>(to_parrent()) : Error(); }

	template<typename _Result, typename _Error>
	SCT_ArgsP_INL VariantResult<_Result, _Error>::Base&
		VariantResult<_Result, _Error>::to_parrent() noexcept
		{ return static_cast<Base&>(*this); }

	template<typename _Result, typename _Error>
	SCT_ArgsP_INL const VariantResult<_Result, _Error>::Base&
		VariantResult<_Result, _Error>::to_parrent() const noexcept
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
