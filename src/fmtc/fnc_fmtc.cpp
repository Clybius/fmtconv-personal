/*****************************************************************************

        fnc.cpp
        Author: Laurent de Soras, 2015

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "fmtc/fnc.h"
#include "fmtcl/fnc.h"
#include "fmtcl/MatrixProc.h"
#include "vsutl/FilterBase.h"
#include "vsutl/fnc.h"
#include "VapourSynth4.h"

#include <algorithm>

#include <cassert>



namespace fmtc
{



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

	
	
/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



fmtcl::PicFmt	conv_vsfmt_to_picfmt (const ::VSVideoFormat &fmt, bool full_flag)
{
	fmtcl::PicFmt  pic_fmt;
	pic_fmt._sf        = conv_vsfmt_to_splfmt (fmt);
	pic_fmt._res       = fmt.bitsPerSample;
	pic_fmt._col_fam   = conv_vsfmt_to_colfam (fmt);
	pic_fmt._full_flag = full_flag;

	return pic_fmt;
}



fmtcl::SplFmt	conv_vsfmt_to_splfmt (const ::VSVideoFormat &fmt)
{
	fmtcl::SplFmt  splfmt = fmtcl::SplFmt_ILLEGAL;

	if (fmt.sampleType == ::stFloat && fmt.bitsPerSample == 32)
	{
		splfmt = fmtcl::SplFmt_FLOAT;
	}
	else
	{
		if (fmt.bitsPerSample <= 8)
		{
			splfmt = fmtcl::SplFmt_INT8;
		}
		else if (fmt.bitsPerSample <= 16)
		{
			splfmt = fmtcl::SplFmt_INT16;
		}
	}

	return splfmt;
}



void	conv_vsfmt_to_splfmt (fmtcl::SplFmt &type, int &bitdepth, const ::VSVideoFormat &fmt)
{
	type     = conv_vsfmt_to_splfmt (fmt);
	bitdepth = fmt.bitsPerSample;
}



fmtcl::ColorFamily	conv_vsfmt_to_colfam (const ::VSVideoFormat &fmt)
{
	auto          col_fam = fmtcl::ColorFamily_INVALID;

	switch (fmt.colorFamily)
	{
	case cfGray:
		col_fam = fmtcl::ColorFamily_GRAY;
		break;
	case cfRGB:
		col_fam = fmtcl::ColorFamily_RGB;
		break;
	case cfYUV:
		col_fam = fmtcl::ColorFamily_YUV;
		break;
	default:
		assert (false);
		break;
	}

	return col_fam;
}



int	conv_fmtcl_colfam_to_vs (fmtcl::ColorFamily cf)
{
	assert (cf >= 0);
	assert (cf < fmtcl::ColorFamily_NBR_ELT);

	int            vs_cf = ::cfUndefined;
	switch (cf)
	{
	case fmtcl::ColorFamily_GRAY: vs_cf = ::cfGray; break;
	case fmtcl::ColorFamily_RGB:  vs_cf = ::cfRGB;  break;
	case fmtcl::ColorFamily_YUV:  vs_cf = ::cfYUV;  break;
	default:
		assert (false);
		break;
	}

	return vs_cf;
}



void	prepare_matrix_coef (const vsutl::FilterBase &filter, fmtcl::MatrixProc &mat_proc, const fmtcl::Mat4 &mat_main, const ::VSVideoFormat &fmt_dst, bool full_range_dst_flag, const ::VSVideoFormat &fmt_src, bool full_range_src_flag, fmtcl::ColorSpaceH265 csp_out, int plane_out)
{
	const fmtcl::PicFmt  fmt_src_fmtcl =
		conv_vsfmt_to_picfmt (fmt_src, full_range_src_flag);
	const fmtcl::PicFmt  fmt_dst_fmtcl =
		conv_vsfmt_to_picfmt (fmt_dst, full_range_dst_flag);

	const int      ret_val = fmtcl::prepare_matrix_coef (
		mat_proc, mat_main, fmt_dst_fmtcl, fmt_src_fmtcl, csp_out, plane_out
	);

	if (ret_val != fmtcl::MatrixProc::Err_OK)
	{
		if (ret_val == fmtcl::MatrixProc::Err_POSSIBLE_OVERFLOW)
		{
			filter.throw_inval_arg (
				"one of the coefficients could cause an overflow."
			);
		}
		else if (ret_val == fmtcl::MatrixProc::Err_TOO_BIG_COEF)
		{
			filter.throw_inval_arg (
				"too big matrix coefficient."
			);
		}
		else if (ret_val == fmtcl::MatrixProc::Err_INVALID_FORMAT_COMBINATION)
		{
			filter.throw_inval_arg (
				"invalid frame format combination."
			);
		}
		else
		{
			assert (false);
			filter.throw_inval_arg (
				"unidentified error while building the matrix."
			);
		}
	}
}



fmtcl::ProcComp3Arg	build_mat_proc (const ::VSAPI &vsapi, ::VSFrame &dst, const ::VSFrame &src, bool single_plane_flag)
{
	fmtcl::ProcComp3Arg  pa;

	pa._w = vsapi.getFrameWidth (&dst, 0);
	pa._h = vsapi.getFrameHeight (&dst, 0);

	const int      nbr_active_planes = std::min <int> (
		fmtcl::ProcComp3Arg::_nbr_planes,
		vsapi.getVideoFrameFormat (&src)->numPlanes
	);
	assert (nbr_active_planes == 1 || nbr_active_planes == 3);

	for (int p_idx = 0; p_idx < nbr_active_planes; ++p_idx)
	{
		if (! single_plane_flag || p_idx == 0)
		{
			pa._dst [p_idx]._ptr    = vsapi.getWritePtr (&dst, p_idx);
			pa._dst [p_idx]._stride = vsapi.getStride (&dst, p_idx);
		}
		pa._src [p_idx]._ptr    = vsapi.getReadPtr (&src, p_idx);
		pa._src [p_idx]._stride = vsapi.getStride (&src, p_idx);
	}

	return pa;
}



}	// namespace fmtc



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
