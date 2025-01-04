#pragma once

#include "../StringTo.hpp"

#include <charconv>

namespace SCT::ArgsP::DarkSide
{
	template<typename Arit, typename... Base>
	requires std::integral<Arit> || std::floating_point<Arit>
	SCT_ArgsP_INL Error::Result<Arit>
		str_to(std::string_view str, size_t* index, Base... base) noexcept
	{
		static_assert(sizeof...(Base) <= 1, "too many arguments passed");
	
		auto begin = str.data();
		auto end = begin + str.size();

		Arit res;
		auto [ptr, ec] = std::from_chars(begin, end, res, base...);

		switch (ec)
		{
		case std::errc::invalid_argument:
			return Error::Code::invalid_value;
		case std::errc::result_out_of_range:
			return Error::Code::out_of_range;

		default:
			break;
		}

		if (ptr != end)
			return Error::Code::invalid_value;


		if (index)
			*index = ptr - begin;

		return res;
	}
}

namespace SCT::ArgsP
{
	template<std::integral Int>
	SCT_ArgsP_INL Error::Result<Int>
		str_to(std::string_view str, size_t* index, int base) noexcept
		{ return DarkSide::str_to<Int>(str, index, base); }

	template<std::floating_point Float>
	SCT_ArgsP_INL Error::Result<Float>
		str_to(std::string_view str, size_t* index) noexcept
		{ return DarkSide::str_to<Float>(str, index); }
}
