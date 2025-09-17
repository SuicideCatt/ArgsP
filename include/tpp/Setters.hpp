#pragma once

#include "../Setters.hpp"

namespace SCT::ArgsP::Setters
{
	template<std::integral Type, IntBase base>
	SCT_ArgsP_INL Error::Code parse(std::optional<Type>& v, std::string_view new_value)
	{
		int b = 10;
		if constexpr (base == IntBase::automatic)
		{
			if (new_value.size() > 1 && new_value[0] == '0')
			{
				if ((new_value[1] == 'b' || new_value[1] == 'B'))
				{
					new_value = new_value.substr(2);
					b = 2;
				}
				else if ((new_value[1] == 'x' || new_value[1] == 'X'))
				{
					new_value = new_value.substr(2);
					b = 16;
				}
			}
		}
		else
		{
			b = static_cast<int>(base);
		}

		auto res = str_to<Type>(new_value, nullptr, b);
		if (res)
		{
			v = res.value_or(0);
			return Error::Code::no_error;
		}

		return res.error();
	}

	template<std::floating_point Type>
	SCT_ArgsP_INL Error::Code parse(std::optional<Type>& v, std::string_view new_value)
	{
		auto res = str_to<Type>(new_value);
		if (res)
		{
			v = res.value_or(0);
			return Error::Code::no_error;
		}

		return res.error();
	}

	template<std::integral Type, IntBase base>
	SCT_ArgsP_INL Error::Code parse(Type& v, std::string_view new_value)
	{
		int b = 10;
		if constexpr (base == IntBase::automatic)
		{
			if (new_value.size() > 1 && new_value[0] == '0')
			{
				if ((new_value[1] == 'b' || new_value[1] == 'B'))
				{
					new_value = new_value.substr(2);
					b = 2;
				}
				else if ((new_value[1] == 'x' || new_value[1] == 'X'))
				{
					new_value = new_value.substr(2);
					b = 16;
				}
			}
		}
		else
		{
			b = static_cast<int>(base);
		}

		auto res = str_to<Type>(new_value, nullptr, b);
		if (res)
		{
			v = res.value_or(0);
			return Error::Code::no_error;
		}

		return res.error();
	}

	template<std::floating_point Type>
	SCT_ArgsP_INL Error::Code parse(Type& v, std::string_view new_value)
	{
		auto res = str_to<Type>(new_value);
		if (res)
		{
			v = res.value_or(0);
			return Error::Code::no_error;
		}

		return res.error();
	}
}
