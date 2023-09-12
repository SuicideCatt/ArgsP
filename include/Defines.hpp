#pragma once

#ifndef SCT_INL
	#ifdef _MSC_VER
		#define SCT_ArgsP_INL [[msvc::forceinline]] inline
	#else
		#define SCT_ArgsP_INL [[gnu::always_inline]] inline
	#endif
#else
	#define SCT_ArgsP_INL SCT_INL
#endif
