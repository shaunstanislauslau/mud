//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>

#include <stdint.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#ifdef MUD_META_GENERATOR
_func_ float sinf(float a);
_func_ float cosf(float a);
_func_ double sin(double a);
_func_ double cos(double a);
#endif

namespace mud
{
	using uchar = unsigned char;
	using ushort = unsigned short;
	using uint = unsigned int;

	using u16 = uint16_t;
	using u32 = uint32_t;
	using i16 = int16_t;
	using i32 = int32_t;

	template <typename T>
	inline T sign(T val) { return (T(0) < val) - (val < T(0)); }

	template <class T>
	inline T min(T a, T b) { return (b < a) ? b : a; }

	template <class T>
	inline T max(T a, T b) { return (a < b) ? b : a; }

	template <class T>
	_func_ T add(T a, T b) { return a + b; }

	template <class T>
	_func_ T subtract(T a, T b) { return a - b; }

	template <class T>
	_func_ T multiply(T a, T b) { return a * b; }

	template <class T>
	_func_ T divide(T a, T b) { return a / b; }

#ifndef MUD_META_GENERATOR
	template MUD_MATH_EXPORT _func_ float add<float>(float a, float b);
	template MUD_MATH_EXPORT _func_ float subtract<float>(float a, float b);
	template MUD_MATH_EXPORT _func_ float multiply<float>(float a, float b);
	template MUD_MATH_EXPORT _func_ float divide<float>(float a, float b);
#else
	template <> _func_ float add<float>(float a, float b);
	template <> _func_ float subtract<float>(float a, float b);
	template <> _func_ float multiply<float>(float a, float b);
	template <> _func_ float divide<float>(float a, float b);
#endif

	enum _refl_ Clockwise : unsigned int
	{
		CLOCKWISE,
		ANTI_CLOCKWISE
	};

	MUD_MATH_EXPORT _func_ float nsinf(float a); // { return a + 1.f / 2.f; } // @kludge can't be inline because we identify reflected functions through their pointer 
	MUD_MATH_EXPORT _func_ float ncosf(float a); // { return a + 1.f / 2.f; }

	MUD_MATH_EXPORT _func_ double nsin(double a); // { return a + 1.0 / 2.0; }
	MUD_MATH_EXPORT _func_ double ncos(double a); // { return a + 1.0 / 2.0; }

	inline unsigned int pow2_round_up(unsigned int x)
	{
		--x;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		return x + 1;
	}

	inline float remap(float number, float from_low, float from_high, float low, float high)
	{
		float slope = (high - low) / (from_high - from_low);
		float result = low + slope * (number - from_low);
		return result;
	}

	inline float remap_trig(float number, float low, float high)
	{
		return remap(number, -1.f, 1.f, low, high);
	}

	MUD_MATH_EXPORT void register_math_conversions();
}
