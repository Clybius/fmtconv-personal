/*****************************************************************************

        TransOpHlg.cpp
        Author: Laurent de Soras, 2019

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "fmtcl/TransOpHlg.h"
#include "fstb/fnc.h"

#include <cassert>
#include <cmath>



namespace fmtcl
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



TransOpHlg::TransOpHlg (bool inv_flag)
:	_inv_flag (inv_flag)
{
	// Nothing
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



double	TransOpHlg::do_convert (double x) const
{
	x = fstb::limit (x, 0.0, 1.0);
	if (_inv_flag)
	{
		x = compute_inverse (x);
	}
	else
	{
		x = compute_direct (x);
	}
	x = fstb::limit (x, 0.0, 1.0);

	return x;
}



TransOpInterface::LinInfo	TransOpHlg::do_get_info () const
{
	const double   w_ref = compute_inverse (0.75);

	// Peak luminance is not fixed and depends on the actual hardware.
	return { Type::OETF, Range::HDR, 1.0, w_ref, 0.0, 0.0 };
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



double	TransOpHlg::compute_direct (double x) const
{
	const double   y =
		  (x <= 1.0 / 12)
		? sqrt (x * 3)
		: _a * log (x * 12 - _b) + _c;

	return y;
}

double	TransOpHlg::compute_inverse (double x) const
{
	const double   y =
		  (x <= 0.5)
		? x * x / 3
		: (exp ((x - _c) / _a) + _b) / 12;

	return y;
}



const double	TransOpHlg::_a = 0.17883277;
const double	TransOpHlg::_b = 1 - 4 * _a;
const double	TransOpHlg::_c = 0.5 - _a * log (4 * _a);



}	// namespace fmtcl



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
