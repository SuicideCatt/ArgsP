#pragma once

#include "Defines.hpp"

#include "BaseArguments.hpp"

namespace SCT::ArgsP::Flags
{
	struct Info
	{
		SCT_ArgsP_INL
		consteval Info(size_t prefix_count, std::string_view name);

		size_t prefix_count = 0;
		std::string_view name = "";
	};

	using Infos = std::initializer_list<Info>;

	template<typename Type>
	class Base : public Arguments::Base<Type>
	{
	public:
		using SPtr = std::shared_ptr<Base<Type>>;

		SCT_ArgsP_INL Base(const Infos& flags, const Type& base_value);
		SCT_ArgsP_INL virtual ~Base();

	protected:
		std::vector<Info> p_flags;
	};
}

#include "ipp/BaseFlags.hpp"
#include "tpp/BaseFlags.hpp"
