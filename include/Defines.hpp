#pragma once

#ifdef _MSC_VER
	#define SCT_ArgsP_INL [[msvc::forceinline]] inline
#else
	#define SCT_ArgsP_INL [[gnu::always_inline]] inline
#endif
