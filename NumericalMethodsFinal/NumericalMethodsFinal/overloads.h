#pragma once

#ifndef _INC_OVERLOADS
#define _INC_OVERLOADS


template < class T >
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
	os << std::endl;
	for (std::vector<T>::const_iterator i = v.begin(); i != v.end(); ++i)
	{
		os << " " << *i;
	}

	os << std::endl;
	return os;
}

#endif