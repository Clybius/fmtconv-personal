/*****************************************************************************

        fnc.h
        Author: Laurent de Soras, 2011

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (conc_fnc_HEADER_INCLUDED)
#define	conc_fnc_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace conc
{



template <class T>
bool	is_ptr_aligned (const T *ptr, int align) noexcept;
template <class T>
bool	is_ptr_aligned_nz (const T *ptr, int align) noexcept;
template <class T>
bool	is_ptr_aligned_nz (const T *ptr) noexcept;



}	// namespace conc



#include "conc/fnc.hpp"



#endif	// conc_fnc_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
