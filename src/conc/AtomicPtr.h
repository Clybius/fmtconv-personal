/*****************************************************************************

        AtomicPtr.h
        Author: Laurent de Soras, 2011

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (conc_AtomicPtr_HEADER_INCLUDED)
#define	conc_AtomicPtr_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "conc/def.h"

#if (conc_ARCHI != conc_ARCHI_X86)
	#include <atomic>
#endif



namespace conc
{



template <class T>
class AtomicPtr
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	inline         AtomicPtr () noexcept;
	inline         AtomicPtr (T *ptr) noexcept;
	inline AtomicPtr <T> &
	               operator = (T *other_ptr) noexcept;

	inline         operator T * () const noexcept;

	bool           operator == (T *other_ptr) const noexcept;
	bool           operator != (T *other_ptr) const noexcept;

	inline T *     swap (T *other_ptr) noexcept;
	inline T *     cas (T *other_ptr, T *comp_ptr) noexcept;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	inline T *     read_ptr () const noexcept;

#if (conc_ARCHI == conc_ARCHI_X86)

	static_assert ((conc_WORD_SIZE_BYTE == sizeof (T*)), "");

	union PtrMixed
	{
		T    *        _t_ptr;
		void *        _void_ptr;
	};

	conc_TYPEDEF_ALIGN (conc_WORD_SIZE_BYTE, PtrMixed, PtrAlign);

	volatile PtrAlign
	               _ptr;

#else  // conc_ARCHI

#if (__cplusplus >= 201703L)
	static_assert (
		std::atomic <T *>::is_always_lock_free,
		"Atomic data must be lock-free."
	);
#endif
	std::atomic <T *>
	               _ptr;

#endif // conc_ARCHI



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	bool           operator == (const AtomicPtr <T> &other) const = delete;
	bool           operator != (const AtomicPtr <T> &other) const = delete;

};	// class AtomicPtr



}	// namespace conc



#include "conc/AtomicPtr.hpp"



#endif	// conc_AtomicPtr_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
