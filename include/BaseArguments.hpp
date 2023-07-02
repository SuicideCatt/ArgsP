#pragma once

#include "Defines.hpp"

#include "Base.hpp"

namespace SCT::ArgsP::Arguments
{
	template<typename  Type>
	class Base : public ArgsP::Base
	{
	public:
		using element_type = Type;
		using reference = Type&;
		using const_reference = const Type&;

		using SPtr = std::shared_ptr<Base<Type>>;

		SCT_ArgsP_INL Base(const Type& base_value);
		SCT_ArgsP_INL virtual ~Base();

		SCT_ArgsP_INL const Type& get() const noexcept;

	protected:
		Type p_value;
	};
}

#include "tpp/BaseArguments.hpp"
