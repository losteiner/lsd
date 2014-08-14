/*!
 * @file lsd_types.hpp
 *
 * @author David Losteiner
 * @date 2014.08.11.
 *
 * Basic types are defined here: integers, floats, etc.
 *
 */

#pragma once

namespace lsd
{
	// ----- Integer typedefs -----

	/// Unsigned 8bit integer
	typedef unsigned char uint8_t;
	/// Signed 8bit integer
	typedef   signed char int8_t;
	
	/// Unsigned 16bit integer
	typedef unsigned short uint16_t;
	/// Signed 16bit integer
	typedef   signed short int16_t;
	
	/// Unsigned 32bit integer
	typedef unsigned int uint32_t;
	/// Signed 32bit integer
	typedef   signed int int32_t;

	/// Unsigned 64bit integer
	typedef unsigned long long uint64_t;
	/// Signed 64 bit integer
	typedef   signed long long int64_t;
	
	/// Raw byte
	typedef char byte_t;
	

	// ----- Floating point typedefs -----

	/// Floating point number on 32bit
	typedef  float float32_t;
	/// Floating point number on 64bit
	typedef double float64_t;
	
}
