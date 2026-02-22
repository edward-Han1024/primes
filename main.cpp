// main.cpp: file containing everything (almost)
// Copyright (C) 2024-2026  Edward Han

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

/* this file follows GNU style formatting. Tab width is 8 */

#pragma region includes
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdint>
// #include <chrono>
// #include <algorithm>
// #define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
// #include <boost/dynamic_bitset/dynamic_bitset.hpp>
// #include <mutex>
// #include <thread>
#pragma endregion includes

#pragma region defs
// #define DEBUG 1
// #define BINARY 1
#ifdef DEBUG
constexpr int debug = 1;
#else
constexpr int debug = 0;
#endif
#define ulong uint64_t

#ifdef __wasi__
extern "C"
{
  _LIBCPP_OVERRIDABLE_FUNC_VIS void *__cxa_allocate_exception(size_t)
  {
    abort();
  }

  void __cxa_throw()
  {
    abort();
  }
}
#endif

#ifdef EMSCRIPTEN
extern "C"
{
  void __cxa_throw()
  {
    abort();
  }
}
#endif
#pragma endregion defs

#pragma region bitdefs
constexpr unsigned char BIT1 = 0b10000000;
constexpr unsigned char BIT2 = 0b01000000;
constexpr unsigned char BIT3 = 0b00100000;
constexpr unsigned char BIT4 = 0b00010000;
constexpr unsigned char BIT5 = 0b00001000;
constexpr unsigned char BIT6 = 0b00000100;
constexpr unsigned char BIT7 = 0b00000010;
constexpr unsigned char BIT8 = 0b00000001;

constexpr unsigned char NBIT1 = ~BIT1;
constexpr unsigned char NBIT2 = ~BIT2;
constexpr unsigned char NBIT3 = ~BIT3;
constexpr unsigned char NBIT4 = ~BIT4;
constexpr unsigned char NBIT5 = ~BIT5;
constexpr unsigned char NBIT6 = ~BIT6;
constexpr unsigned char NBIT7 = ~BIT7;
constexpr unsigned char NBIT8 = ~BIT8;
#pragma endregion bitdefs

#pragma region debugfunctions
// print a debug message for setting a bit.
void debugprint(uint64_t byte, uint16_t bit)
{
  if (debug)
    {
      std::cout << "[DEBUG] Set byte " << byte << " and bit " << bit << " to 0." << std::endl;
    }
}

// print a debug message for unsetting a bit.
void debugreset(uint64_t byte, uint16_t bit)
{
  if(debug)
    {
      std::cout << "[DEBUG] Reset byte " << byte << " bit " << bit << " to 1." << std::endl;
    }
}

// print a debug message for finding a prime.
void foundprimes(uint64_t byte, uint16_t bit)
{
  if(debug)
    {
      std::cout << "[DEBUG] Found prime at byte " << byte << " bit " << bit << " which equals ";
      switch(bit)
	{
	case(1):
	  std::cout << byte * 30 + 1;
	  break;
	case(2):
	  std::cout << byte * 30 + 7;
	  break;
	case(3):
	  std::cout << byte * 30 + 11;
	  break;
	case(4):
	  std::cout << byte * 30 + 13;
	  break;
	case(5):
	  std::cout << byte * 30 + 17;
	  break;
	case(6):
	  std::cout << byte * 30 + 19;
	  break;
	case(7):
	  std::cout << byte * 30 + 23;
	  break;
	case(8):
	  std::cout << byte * 30 + 29;
	  break;
	default:
	  std::cerr << "[Error] Invalid bit found";
	  break;
	}
      std::cout << "." << std::endl;
    }
}
#pragma endregion debugfunctions

#pragma region sieve30
// compute the unsegmented sieve up to the given end ignoring all multiples of 2, 3 and 5.
int sieve30(unsigned long end)
{
  // The length of the vector would be the next largest multiple of 30
  const unsigned long length = std::ceil(end / 30.);
  if (length * 30 != end){
    std::cerr << "Warning: end is not divisible by 30" << std::endl;
    std::cerr << "Warning: length might be longer than expected" << std::endl;
  }
  std::vector<unsigned char> primes(length, 0b11111111);
  // 1 should not be assumed to be prime
  // doing so would cause all numbers to be composite.
  primes[0] &= NBIT1;
  // We must search up to the square root
  uint64_t nCycle;
  uint64_t whichByte;
  for (uint64_t nByte = 0; nByte <= std::ceil(std::sqrt(end) / 30.); ++nByte)
    {
      if ((primes[nByte] & BIT1) != 0)
	{
	  if(debug) foundprimes(nByte, 1);
	  for (nCycle = nByte; (30 * nByte + 1) * nCycle + 29 * nByte < length; ++nCycle)
	    {
	      whichByte = (30 * nByte + 1) * nCycle;
	      if (debug)
		{
		  debugprint(whichByte + nByte, 1);
		  debugprint(whichByte + 7 * nByte, 2);
		  debugprint(whichByte + 11 * nByte, 3);
		  debugprint(whichByte + 13 * nByte, 4);
		  debugprint(whichByte + 17 * nByte, 5);
		  debugprint(whichByte + 19 * nByte, 6);
		  debugprint(whichByte + 23 * nByte, 7);
		  debugprint(whichByte + 29 * nByte, 8);
		  std::cout << std::endl;
		}
	      primes[whichByte + nByte] &= NBIT1;
	      primes[whichByte + nByte * 7] &= NBIT2;
	      primes[whichByte + nByte * 11] &= NBIT3;
	      primes[whichByte + nByte * 13] &= NBIT4;
	      primes[whichByte + nByte * 17] &= NBIT5;
	      primes[whichByte + nByte * 19] &= NBIT6;
	      primes[whichByte + nByte * 23] &= NBIT7;
	      primes[whichByte + nByte * 29] &= NBIT8;
	    }
	  whichByte = (30 * nByte + 1) * nCycle;
	  uint8_t number = 0;
	  if(whichByte + nByte * 23 < length)
	    number = 7;
	  else if (whichByte + nByte * 19 < length)
	    number = 6;
	  else if (whichByte + nByte * 17 < length)
	    number = 5;
	  else if (whichByte + nByte * 13 < length)
	    number = 4;
	  else if (whichByte + nByte * 11 < length)
	    number = 3;
	  else if (whichByte + nByte * 7 < length)
	    number = 2;
	  else if (whichByte + nByte < length)
	    number = 1;
	  switch(number)
	    {
	    case(7):
	      primes[whichByte + nByte * 23] &= NBIT7;
	      if(debug) debugprint(whichByte + nByte * 23, 7);
	    case(6):
	      primes[whichByte + nByte * 19] &= NBIT6;
	      if(debug) debugprint(whichByte + nByte * 19, 6);
	    case(5):
	      primes[whichByte + nByte * 17] &= NBIT5;
	      if(debug) debugprint(whichByte + nByte * 17, 5);
	    case(4):
	      primes[whichByte + nByte * 13] &= NBIT4;
	      if(debug) debugprint(whichByte + nByte * 13, 4);
	    case(3):
	      primes[whichByte + nByte * 11] &= NBIT3;
	      if(debug) debugprint(whichByte + nByte * 11, 3);
	    case(2):
	      primes[whichByte + nByte * 7] &= NBIT2;
	      if(debug) debugprint(whichByte + nByte * 7, 2);
	    case(1):
	      primes[whichByte + nByte] &= NBIT1;
	      if(debug) debugprint(whichByte + nByte, 1);
	    }
	  primes[nByte] |= BIT1;
	  if(debug)
	    {
	      debugreset(nByte, 1);
	      std::cout << std::endl;
	    }
	}
      if ((primes[nByte] & BIT2) != 0)
	{
	  if(debug) foundprimes(nByte, 2);
	  for (nCycle = nByte; (30 * nByte + 7) * nCycle + 29 * nByte + 6 < length; ++nCycle)
	    {
	      whichByte = (30 * nByte + 7) * nCycle;
	      if (debug)
		{
		  debugprint(whichByte + nByte, 2);
		  debugprint(whichByte + 7 * nByte + 1, 6);
		  debugprint(whichByte + 11 * nByte + 2, 5);
		  debugprint(whichByte + 13 * nByte + 3, 1);
		  debugprint(whichByte + 17 * nByte + 3, 8);
		  debugprint(whichByte + 19 * nByte + 4, 4);
		  debugprint(whichByte + 23 * nByte + 5, 3);
		  debugprint(whichByte + 29 * nByte + 6, 7);
		  std::cout << std::endl;
		}
	      primes[whichByte + nByte] &= NBIT2;
	      primes[whichByte + nByte * 7 + 1] &= NBIT6;
	      primes[whichByte + nByte * 11 + 2] &= NBIT5;
	      primes[whichByte + nByte * 13 + 3] &= NBIT1;
	      primes[whichByte + nByte * 17 + 3] &= NBIT8;
	      primes[whichByte + nByte * 19 + 4] &= NBIT4;
	      primes[whichByte + nByte * 23 + 5] &= NBIT3;
	      primes[whichByte + nByte * 29 + 6] &= NBIT7;
	    }
	  whichByte = (30 * nByte + 7) * nCycle;
	  uint8_t number = 0;
	  if(whichByte + nByte * 23 + 5 < length)
	    number = 7;
	  else if (whichByte + nByte * 19 + 4 < length)
	    number = 6;
	  else if (whichByte + nByte * 17 + 3 < length)
	    number = 5;
	  else if (whichByte + nByte * 13 + 3 < length)
	    number = 4;
	  else if (whichByte + nByte * 11 + 2 < length)
	    number = 3;
	  else if (whichByte + nByte * 7 + 1 < length)
	    number = 2;
	  else if (whichByte + nByte < length)
	    number = 1;
	  switch(number)
	    {
	    case(7):
	      primes[whichByte + nByte * 23 + 5] &= NBIT3;
	      if(debug) debugprint(whichByte + nByte * 23 + 5, 3);
	    case(6):
	      primes[whichByte + nByte * 19 + 4] &= NBIT4;
	      if(debug) debugprint(whichByte + nByte * 19 + 4, 4);
	    case(5):
	      primes[whichByte + nByte * 17 + 3] &= NBIT8;
	      if(debug) debugprint(whichByte + nByte * 17 + 3, 8);
	    case(4):
	      primes[whichByte + nByte * 13 + 3] &= NBIT1;
	      if(debug) debugprint(whichByte + nByte * 13 + 3, 1);
	    case(3):
	      primes[whichByte + nByte * 11 + 2] &= NBIT5;
	      if(debug) debugprint(whichByte + nByte * 11 + 2, 5);
	    case(2):
	      primes[whichByte + nByte * 7 + 1] &= NBIT6;
	      if(debug) debugprint(whichByte + nByte * 7 + 1, 6);
	    case(1):
	      primes[whichByte + nByte] &= NBIT2;
	      if(debug) debugprint(whichByte + nByte, 2);
	    }
	  primes[nByte] |= BIT2;
	  if(debug)
	    {
	      debugreset(nByte, 2);
	      std::cout << std::endl;
	    }
	}
      if ((primes[nByte] & BIT3) != 0)
	{
	  if(debug) foundprimes(nByte, 3);
	  for (nCycle = nByte; (30 * nByte + 11) * nCycle + 29 * nByte + 10 < length; ++nCycle)
	    {
	      whichByte = (30 * nByte + 11) * nCycle;
	      if (debug)
		{
		  debugprint(whichByte + nByte, 3);
		  debugprint(whichByte + 7 * nByte + 2, 5);
		  debugprint(whichByte + 11 * nByte + 4, 1);
		  debugprint(whichByte + 13 * nByte + 4, 7);
		  debugprint(whichByte + 17 * nByte + 6, 2);
		  debugprint(whichByte + 19 * nByte + 6, 8);
		  debugprint(whichByte + 23 * nByte + 8, 4);
		  debugprint(whichByte + 29 * nByte + 10, 6);
		  std::cout << std::endl;
		}
	      primes[whichByte + nByte] &= NBIT3;
	      primes[whichByte + nByte * 7 + 2] &= NBIT5;
	      primes[whichByte + nByte * 11 + 4] &= NBIT1;
	      primes[whichByte + nByte * 13 + 4] &= NBIT7;
	      primes[whichByte + nByte * 17 + 6] &= NBIT2;
	      primes[whichByte + nByte * 19 + 6] &= NBIT8;
	      primes[whichByte + nByte * 23 + 8] &= NBIT4;
	      primes[whichByte + nByte * 29 + 10] &= NBIT6;
	    }
	  whichByte = (30 * nByte + 11) * nCycle;
	  uint8_t number = 0;
	  if(whichByte + nByte * 23 + 8 < length)
	    number = 7;
	  else if (whichByte + nByte * 19 + 6 < length)
	    number = 6;
	  else if (whichByte + nByte * 17 + 6 < length)
	    number = 5;
	  else if (whichByte + nByte * 13 + 4 < length)
	    number = 4;
	  else if (whichByte + nByte * 11 + 4 < length)
	    number = 3;
	  else if (whichByte + nByte * 7 + 2 < length)
	    number = 2;
	  else if (whichByte + nByte < length)
	    number = 1;
	  switch(number)
	    {
	    case(7):
	      primes[whichByte + nByte * 23 + 8] &= NBIT4;
	      debugprint(whichByte + nByte * 23 + 8, 4);
	    case(6):
	      primes[whichByte + nByte * 19 + 6] &= NBIT8;
	      debugprint(whichByte + nByte * 19 + 6, 8);
	    case(5):
	      primes[whichByte + nByte * 17 + 6] &= NBIT2;
	      debugprint(whichByte + nByte * 17 + 6, 2);
	    case(4):
	      primes[whichByte + nByte * 13 + 4] &= NBIT7;
	      debugprint(whichByte + nByte * 13 + 4, 7);
	    case(3):
	      primes[whichByte + nByte * 11 + 4] &= NBIT1;
	      debugprint(whichByte + nByte * 11 + 4, 1);
	    case(2):
	      primes[whichByte + nByte * 7 + 2] &= NBIT5;
	      debugprint(whichByte + nByte * 7 + 2, 5);
	    case(1):
	      primes[whichByte + nByte] &= NBIT3;
	      debugprint(whichByte + nByte, 3);
	    }
	  primes[nByte] |= BIT3;
	  if(debug)
	    {
	      debugreset(nByte, 3);
	      std::cout << std::endl;
	    }
	}
      if ((primes[nByte] & BIT4) != 0)
	{
	  if(debug) foundprimes(nByte, 4);
	  for (nCycle = nByte; (30 * nByte + 13) * nCycle + 29 * nByte + 12 < length; ++nCycle)
	    {
	      whichByte = (30 * nByte + 13) * nCycle;
	      if (debug)
		{
		  debugprint(whichByte + nByte, 4);
		  debugprint(whichByte + 7 * nByte + 3, 1);
		  debugprint(whichByte + 11 * nByte + 4, 7);
		  debugprint(whichByte + 13 * nByte + 5, 6);
		  debugprint(whichByte + 17 * nByte + 7, 3);
		  debugprint(whichByte + 19 * nByte + 8, 2);
		  debugprint(whichByte + 23 * nByte + 9, 8);
		  debugprint(whichByte + 29 * nByte + 12, 5);
		  std::cout << std::endl;
		}
	      primes[whichByte + nByte] &= NBIT4;
	      primes[whichByte + nByte * 7 + 3] &= NBIT1;
	      primes[whichByte + nByte * 11 + 4] &= NBIT7;
	      primes[whichByte + nByte * 13 + 5] &= NBIT6;
	      primes[whichByte + nByte * 17 + 7] &= NBIT3;
	      primes[whichByte + nByte * 19 + 8] &= NBIT2;
	      primes[whichByte + nByte * 23 + 9] &= NBIT8;
	      primes[whichByte + nByte * 29 + 12] &= NBIT5;
	    }
	  whichByte = (30 * nByte + 13) * nCycle;
	  uint8_t number = 0;
	  if(whichByte + nByte * 23 + 9 < length)
	    number = 7;
	  else if (whichByte + nByte * 19 + 8 < length)
	    number = 6;
	  else if (whichByte + nByte * 17 + 7 < length)
	    number = 5;
	  else if (whichByte + nByte * 13 + 5 < length)
	    number = 4;
	  else if (whichByte + nByte * 11 + 4 < length)
	    number = 3;
	  else if (whichByte + nByte * 7 + 3 < length)
	    number = 2;
	  else if (whichByte + nByte < length)
	    number = 1;
	  switch(number)
	    {
	    case(7):
	      primes[whichByte + nByte * 23 + 9] &= NBIT8;
	      debugprint(whichByte + nByte * 23 + 9, 8);
	    case(6):
	      primes[whichByte + nByte * 19 + 8] &= NBIT2;
	      debugprint(whichByte + nByte * 19 + 8, 2);
	    case(5):
	      primes[whichByte + nByte * 17 + 7] &= NBIT3;
	      debugprint(whichByte + nByte * 17 + 7, 3);
	    case(4):
	      primes[whichByte + nByte * 13 + 5] &= NBIT6;
	      debugprint(whichByte + nByte * 13 + 5, 6);
	    case(3):
	      primes[whichByte + nByte * 11 + 4] &= NBIT7;
	      debugprint(whichByte + nByte * 11 + 4, 7);
	    case(2):
	      primes[whichByte + nByte * 7 + 3] &= NBIT1;
	      debugprint(whichByte + nByte * 7 + 3, 1);
	    case(1):
	      primes[whichByte + nByte] &= NBIT4;
	      debugprint(whichByte + nByte, 4);
	    }
	  primes[nByte] |= BIT4;
	  if(debug)
	    {
	      debugreset(nByte, 4);
	      std::cout << std::endl;
	    }
	}
      if ((primes[nByte] & BIT5) != 0)
	{
	  if(debug) foundprimes(nByte, 5);
	  for (nCycle = nByte; (30 * nByte + 17) * nCycle + 29 * nByte + 16 < length; ++nCycle)
	    {
	      uint64_t whichByte = (30 * nByte + 17) * nCycle;
	      if (debug)
		{
		  debugprint(whichByte + nByte, 5);
		  debugprint(whichByte + 7 * nByte + 3, 8);
		  debugprint(whichByte + 11 * nByte + 6, 2);
		  debugprint(whichByte + 13 * nByte + 7, 3);
		  debugprint(whichByte + 17 * nByte + 9, 6);
		  debugprint(whichByte + 19 * nByte + 10, 7);
		  debugprint(whichByte + 23 * nByte + 13, 1);
		  debugprint(whichByte + 29 * nByte + 16, 4);
		  std::cout << std::endl;
		}
	      primes[whichByte + nByte] &= NBIT5;
	      primes[whichByte + nByte * 7 + 3] &= NBIT8;
	      primes[whichByte + nByte * 11 + 6] &= NBIT2;
	      primes[whichByte + nByte * 13 + 7] &= NBIT3;
	      primes[whichByte + nByte * 17 + 9] &= NBIT6;
	      primes[whichByte + nByte * 19 + 10] &= NBIT7;
	      primes[whichByte + nByte * 23 + 13] &= NBIT1;
	      primes[whichByte + nByte * 29 + 16] &= NBIT4;
	    }
	  whichByte = (30 * nByte + 17) * nCycle;
	  uint8_t number = 0;
	  if(whichByte + nByte * 23 + 13 < length)
	    number = 7;
	  else if (whichByte + nByte * 19 + 10 < length)
	    number = 6;
	  else if (whichByte + nByte * 17 + 9 < length)
	    number = 5;
	  else if (whichByte + nByte * 13 + 7 < length)
	    number = 4;
	  else if (whichByte + nByte * 11 + 6 < length)
	    number = 3;
	  else if (whichByte + nByte * 7 + 3 < length)
	    number = 2;
	  else if (whichByte + nByte < length)
	    number = 1;
	  switch(number)
	    {
	    case(7):
	      primes[whichByte + nByte * 23 + 13] &= NBIT1;
	      debugprint(whichByte + nByte * 23 + 13, 1);
	    case(6):
	      primes[whichByte + nByte * 19 + 10] &= NBIT7;
	      debugprint(whichByte + nByte * 19 + 10, 7);
	    case(5):
	      primes[whichByte + nByte * 17 + 9] &= NBIT6;
	      debugprint(whichByte + nByte * 17 + 9, 6);
	    case(4):
	      primes[whichByte + nByte * 13 + 7] &= NBIT3;
	      debugprint(whichByte + nByte * 13 + 7, 3);
	    case(3):
	      primes[whichByte + nByte * 11 + 6] &= NBIT2;
	      debugprint(whichByte + nByte * 11 + 6, 2);
	    case(2):
	      primes[whichByte + nByte * 7 + 3] &= NBIT8;
	      debugprint(whichByte + nByte * 7 + 3, 8);
	    case(1):
	      primes[whichByte + nByte] &= NBIT5;
	      debugprint(whichByte + nByte, 5);
	    }
	  primes[nByte] |= BIT5;
	  if(debug)
	    {
	      debugreset(nByte, 5);
	      std::cout << std::endl;
	    }
	}
      if ((primes[nByte] & BIT6) != 0)
	{
	  if(debug) foundprimes(nByte, 6);
	  for (nCycle = nByte; (30 * nByte + 19) * nCycle + 29 * nByte + 18 < length; ++nCycle)
	    {
	      uint64_t whichByte = (30 * nByte + 19) * nCycle;
	      if (debug)
		{
		  debugprint(whichByte + nByte, 6);
		  debugprint(whichByte + 7 * nByte + 4, 4);
		  debugprint(whichByte + 11 * nByte + 6, 8);
		  debugprint(whichByte + 13 * nByte + 8, 2);
		  debugprint(whichByte + 17 * nByte + 10, 7);
		  debugprint(whichByte + 19 * nByte + 12, 1);
		  debugprint(whichByte + 23 * nByte + 14, 5);
		  debugprint(whichByte + 29 * nByte + 18, 3);
		  std::cout << std::endl;
		}
	      primes[whichByte + nByte] &= NBIT6;
	      primes[whichByte + nByte * 7 + 4] &= NBIT4;
	      primes[whichByte + nByte * 11 + 6] &= NBIT8;
	      primes[whichByte + nByte * 13 + 8] &= NBIT2;
	      primes[whichByte + nByte * 17 + 10] &= NBIT7;
	      primes[whichByte + nByte * 19 + 12] &= NBIT1;
	      primes[whichByte + nByte * 23 + 14] &= NBIT5;
	      primes[whichByte + nByte * 29 + 18] &= NBIT3;
	    }
	  whichByte = (30 * nByte + 19) * nCycle;
	  uint8_t number = 0;
	  if(whichByte + nByte * 23 + 14 < length)
	    number = 7;
	  else if (whichByte + nByte * 19 + 12 < length)
	    number = 6;
	  else if (whichByte + nByte * 17 + 10 < length)
	    number = 5;
	  else if (whichByte + nByte * 13 + 8 < length)
	    number = 4;
	  else if (whichByte + nByte * 11 + 6 < length)
	    number = 3;
	  else if (whichByte + nByte * 7 + 4 < length)
	    number = 2;
	  else if (whichByte + nByte < length)
	    number = 1;
	  switch(number)
	    {
	    case(7):
	      primes[whichByte + nByte * 23 + 14] &= NBIT5;
	      debugprint(whichByte + nByte * 23 + 14, 5);
	    case(6):
	      primes[whichByte + nByte * 19 + 12] &= NBIT1;
	      debugprint(whichByte + nByte * 19 + 12, 1);
	    case(5):
	      primes[whichByte + nByte * 17 + 10] &= NBIT7;
	      debugprint(whichByte + nByte * 17 + 10, 7);
	    case(4):
	      primes[whichByte + nByte * 13 + 8] &= NBIT2;
	      debugprint(whichByte + nByte * 13 + 8, 2);
	    case(3):
	      primes[whichByte + nByte * 11 + 6] &= NBIT8;
	      debugprint(whichByte + nByte * 11 + 6, 8);
	    case(2):
	      primes[whichByte + nByte * 7 + 4] &= NBIT4;
	      debugprint(whichByte + nByte * 7 + 4, 4);
	    case(1):
	      primes[whichByte + nByte] &= NBIT6;
	      debugprint(whichByte + nByte, 6);
	    }
	  primes[nByte] |= BIT6;
	  if(debug)
	    {
	      debugreset(nByte, 6);
	      std::cout << std::endl;
	    }
	}
      if ((primes[nByte] & BIT7) != 0)
	{
	  if(debug) foundprimes(nByte, 7);
	  for (nCycle = nByte; (30 * nByte + 23) * nCycle + 29 * nByte + 22 < length; ++nCycle)
	    {
	      uint64_t whichByte = (30 * nByte + 23) * nCycle;
	      if (debug)
		{
		  debugprint(whichByte + nByte, 7);
		  debugprint(whichByte + 7 * nByte + 5, 3);
		  debugprint(whichByte + 11 * nByte + 8, 4);
		  debugprint(whichByte + 13 * nByte + 9, 8);
		  debugprint(whichByte + 17 * nByte + 13, 1);
		  debugprint(whichByte + 19 * nByte + 14, 5);
		  debugprint(whichByte + 23 * nByte + 17, 6);
		  debugprint(whichByte + 29 * nByte + 22, 2);
		  std::cout << std::endl;
		}
	      primes[whichByte + nByte] &= NBIT7;
	      primes[whichByte + nByte * 7 + 5] &= NBIT3;
	      primes[whichByte + nByte * 11 + 8] &= NBIT4;
	      primes[whichByte + nByte * 13 + 9] &= NBIT8;
	      primes[whichByte + nByte * 17 + 13] &= NBIT1;
	      primes[whichByte + nByte * 19 + 14] &= NBIT5;
	      primes[whichByte + nByte * 23 + 17] &= NBIT6;
	      primes[whichByte + nByte * 29 + 22] &= NBIT2;
	    }
	  whichByte = (30 * nByte + 23) * nCycle;
	  uint8_t number = 0;
	  if(whichByte + nByte * 23 + 17 < length)
	    number = 7;
	  else if (whichByte + nByte * 19 + 14 < length)
	    number = 6;
	  else if (whichByte + nByte * 17 + 13 < length)
	    number = 5;
	  else if (whichByte + nByte * 13 + 9 < length)
	    number = 4;
	  else if (whichByte + nByte * 11 + 8 < length)
	    number = 3;
	  else if (whichByte + nByte * 7 + 5 < length)
	    number = 2;
	  else if (whichByte + nByte < length)
	    number = 1;
	  switch(number)
	    {
	    case(7):
	      primes[whichByte + nByte * 23 + 17] &= NBIT6;
	      debugprint(whichByte + nByte * 23 + 17, 6);
	    case(6):
	      primes[whichByte + nByte * 19 + 14] &= NBIT5;
	      debugprint(whichByte + nByte * 19 + 14, 5);
	    case(5):
	      primes[whichByte + nByte * 17 + 13] &= NBIT1;
	      debugprint(whichByte + nByte * 17 + 13, 1);
	    case(4):
	      primes[whichByte + nByte * 13 + 9] &= NBIT8;
	      debugprint(whichByte + nByte * 13 + 9, 8);
	    case(3):
	      primes[whichByte + nByte * 11 + 8] &= NBIT4;
	      debugprint(whichByte + nByte * 11 + 8, 4);
	    case(2):
	      primes[whichByte + nByte * 7 + 5] &= NBIT3;
	      debugprint(whichByte + nByte * 7 + 5, 3);
	    case(1):
	      primes[whichByte + nByte] &= NBIT7;
	      debugprint(whichByte + nByte, 7);
	    }
	  primes[nByte] |= BIT7;
	  if(debug)
	    {
	      debugreset(nByte, 7);
	      std::cout << std::endl;
	    }
	}
      if ((primes[nByte] & BIT8) != 0)
	{
	  if(debug) foundprimes(nByte, 8);
	  for (nCycle = nByte; (30 * nByte + 29) * nCycle + 29 * nByte + 28 < length; ++nCycle)
	    {
	      uint64_t whichByte = (30 * nByte + 29) * nCycle;
	      if (debug)
		{
		  debugprint(whichByte + nByte, 8);
		  debugprint(whichByte + 7 * nByte + 6, 7);
		  debugprint(whichByte + 11 * nByte + 10, 6);
		  debugprint(whichByte + 13 * nByte + 12, 5);
		  debugprint(whichByte + 17 * nByte + 16, 4);
		  debugprint(whichByte + 19 * nByte + 18, 3);
		  debugprint(whichByte + 23 * nByte + 22, 2);
		  debugprint(whichByte + 29 * nByte + 28, 1);
		  std::cout << std::endl;
		}
	      primes[whichByte + nByte] &= NBIT8;
	      primes[whichByte + nByte * 7 + 6] &= NBIT7;
	      primes[whichByte + nByte * 11 + 10] &= NBIT6;
	      primes[whichByte + nByte * 13 + 12] &= NBIT5;
	      primes[whichByte + nByte * 17 + 16] &= NBIT4;
	      primes[whichByte + nByte * 19 + 18] &= NBIT3;
	      primes[whichByte + nByte * 23 + 22] &= NBIT2;
	      primes[whichByte + nByte * 29 + 28] &= NBIT1;
	    }
	  whichByte = (30 * nByte + 29) * nCycle;
	  uint8_t number = 0;
	  if(whichByte + nByte * 23 + 22 < length)
	    number = 7;
	  else if (whichByte + nByte * 18 + 18 < length)
	    number = 6;
	  else if (whichByte + nByte * 16 + 16 < length)
	    number = 5;
	  else if (whichByte + nByte * 12 + 12 < length)
	    number = 4;
	  else if (whichByte + nByte * 10 + 10 < length)
	    number = 3;
	  else if (whichByte + nByte * 6 + 6 < length)
	    number = 2;
	  else if (whichByte + nByte < length)
	    number = 1;
	  switch(number)
	    {
	    case(7):
	      primes[whichByte + nByte * 23 + 22] &= NBIT2;
	      debugprint(whichByte + nByte * 23 + 22, 2);
	    case(6):
	      primes[whichByte + nByte * 19 + 18] &= NBIT3;
	      debugprint(whichByte + nByte * 19 + 18, 3);
	    case(5):
	      primes[whichByte + nByte * 17 + 16] &= NBIT4;
	      debugprint(whichByte + nByte * 17 + 16, 4);
	    case(4):
	      primes[whichByte + nByte * 13 + 12] &= NBIT5;
	      debugprint(whichByte + nByte * 13 + 12, 5);
	    case(3):
	      primes[whichByte + nByte * 11 + 10] &= NBIT6;
	      debugprint(whichByte + nByte * 11 + 10, 6);
	    case(2):
	      primes[whichByte + nByte * 7 + 6] &= NBIT7;
	      debugprint(whichByte + nByte * 7 + 6, 7);
	    case(1):
	      primes[whichByte + nByte] &= NBIT8;
	      debugprint(whichByte + nByte, 8);
	    }
	  primes[nByte] |= BIT8;
	  if(debug)
	    {
	      debugreset(nByte, 8);
	      std::cout << std::endl;
	    }
	}
    }
  std::ofstream file("primes.txt");
  std::string str = "";
  std::for_each(primes.begin(), primes.end(), [&str](unsigned char &c){ str += c; });
  file << str;

  return 0;
}
#pragma endregion sieve30

#pragma region main
int main(int argc, char *argv[])
{
  sieve30(std::stoul(argv[1]));
  return 0;
}
#pragma endregion main
