#pragma once

#ifndef SCT_INL
	// NOTE: If is not work on window... POHUI
	#define SCT_ArgsP_INL [[gnu::always_inline]] inline
#else
	#define SCT_ArgsP_INL SCT_INL
#endif

#ifdef USE_SCT_HM
	#define USE_SCT_ArgsP_HM
#endif

#ifdef USE_SCT_ArgsP_HM
	#define SCT_ArgsP_HM SCT_ArgsP_INL
#else
	#define SCT_ArgsP_HM
#endif
