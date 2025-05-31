/*****************************************************************************

        PrimariesPreset.h
        Copyright (c) 2016 Ohm Force

*Tab=3***********************************************************************/



#pragma once
#if ! defined (fmtcl_PrimariesPreset_HEADER_INCLUDED)
#define fmtcl_PrimariesPreset_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace fmtcl
{



// ITU-T H.265, High efficiency video coding, 2016-06, p. 408
enum PrimariesPreset
{
	PrimariesPreset_INVALID = -2,
	PrimariesPreset_UNDEF   = -1,

	PrimariesPreset_RESERVED0 = 0,
	PrimariesPreset_BT709,
	PrimariesPreset_UNSPECIFIED,
	PrimariesPreset_RESERVED2,
	PrimariesPreset_FCC,
	PrimariesPreset_BT470BG,
	PrimariesPreset_SMPTE170M,
	PrimariesPreset_SMPTE240M,
	PrimariesPreset_GENERIC_FILM,
	PrimariesPreset_BT2020,
	PrimariesPreset_CIEXYZ,
	PrimariesPreset_P3DCI,
	PrimariesPreset_P3D65,

	PrimariesPreset_EBU3213E = 22,

	PrimariesPreset_NBR_ELT,

	PrimariesPreset_ISO_RANGE_LAST = 255,

	PrimariesPreset_NTSCJ,
	PrimariesPreset_SCRGB,
	PrimariesPreset_ADOBE_RGB_98,
	PrimariesPreset_ADOBE_RGB_WIDE,
	PrimariesPreset_APPLE_RGB,
	PrimariesPreset_ROMM,
	PrimariesPreset_CIERGB,
	PrimariesPreset_ACES,
	PrimariesPreset_ACESAP1,
	PrimariesPreset_SGAMUT,
	PrimariesPreset_SGAMUT3CINE,
	PrimariesPreset_ALEXA,
	PrimariesPreset_VGAMUT,
	PrimariesPreset_P3D60,
	PrimariesPreset_P22,
	PrimariesPreset_FREESCALE,
	PrimariesPreset_DAVINCI,
	PrimariesPreset_DRAGONCOLOR,
	PrimariesPreset_DRAGONCOLOR2,
	PrimariesPreset_REDCOLOR,
	PrimariesPreset_REDCOLOR2,
	PrimariesPreset_REDCOLOR3,
	PrimariesPreset_REDCOLOR4,
	PrimariesPreset_REDWIDE,
	PrimariesPreset_P3P,
	PrimariesPreset_CINEGAM,
	PrimariesPreset_AWG4,

	PrimariesPreset_NBR_ELT_CUSTOM
}; // enum PrimariesPreset



}  // namespace fmtcl



//#include "fmtcl/PrimariesPreset.hpp"



#endif   // fmtcl_PrimariesPreset_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
