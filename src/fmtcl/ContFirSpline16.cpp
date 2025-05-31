/*****************************************************************************

        ContFirSpline16.cpp
        Author: Laurent de Soras, 2011

C0 continuity only, derivatives are not continuous.
https://forum.doom9.org/showthread.php?t=147117

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "fmtcl/ContFirSpline16.h"

#include <cmath>



namespace fmtcl
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



double	ContFirSpline16::do_get_support () const
{
	return (2.0);
}



double	ContFirSpline16::do_get_val (double x) const
{
	x = fabs (x);

	double         v = 0;
	if (x < 1.0)
	{
		v = ((           x - 9.0/5.0) * x - 1.0/5.0 ) * x + 1.0;
	}
	else if (x < 2.0)
	{
		x -= 1.0;
		v = ((-1.0/3.0 * x + 4.0/5.0) * x - 7.0/15.0) * x;
	}

	return (v);
}



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}	// namespace fmtcl



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
