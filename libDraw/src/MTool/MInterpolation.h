#ifndef __MINTERPOLATION_H__
#define __MINTERPOLATION_H__
#include "MPlatform.h"
#include "MCommonFunction.h"

class MInterpolation
{
public: 
	template<typename T> inline T getLinerInterpolation(T _from, T _to, float _past, float _delay)
	{
		return _from + static_cast<T>((_to - _from)*(_past / _delay));
	}

	template<typename T> inline T getSineInterpolation(T _from, T _to, float _past, float _delay)
	{
		float s = 0.5f * (1.0f + sin(getLinerInterpolation<float>(-M_PI/2, M_PI/2, _past, _delay)));		
		return _from + static_cast<T>((_to - _from)*s);
	}
protected:
};

#endif