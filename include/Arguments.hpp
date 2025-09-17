#pragma once

#include "Base/Argument.hpp"
#include "Setters.hpp"

namespace SCT::ArgsP::Arguments
{
	template<typename Type, Base::ValueParsePtr<std::optional<Type>> parse_function = nullptr>
	using Base = ArgsP::Base::Argument<std::optional<Type>, parse_function>;

	using String = Base<std::string_view, &Setters::parse>;

	using Int64 = Base<int64_t, &Setters::parse>;
	using UInt64 = Base<uint64_t, &Setters::parse>;

	using Double = Base<double, &Setters::parse>;
}
