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

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdint>
#include <chrono>
#include <algorithm>
#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <mutex>
#include <thread>

// #define DEBUG 1
// #define BINARY 1

// #include "miller-rabin.hpp"
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

// Defs
void basic_sieve(ulong &num, ulong &limit, std::vector<bool> &primes);
std::vector<bool> basic_wrapper(ulong lnum);
long long difference(std::chrono::system_clock::time_point start);
void segmented_sieve(ulong start, ulong end, std::vector<ulong> foundprimes);
int segmented_sieve_worker(std::vector<ulong> &primes);

std::mutex work_mutex;
static ulong start;
static ulong sqrtn;
static ulong num;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        num = 100;
    }
    else
    {
        num = std::stoul(argv[1]);
    }
    sqrtn = sqrt(num);
    if ((sqrtn * sqrtn) != num)
    {
        std::cout << "Warning: end is not a square. This may cause undefined behavior." << std::endl;
    }
    std::cout << "Staring pre-sieve" << std::endl;
    std::vector<bool> presieve = basic_wrapper(sqrt(num));
    std::vector<ulong> primes = {};
    for (unsigned long i = 0; i < presieve.size(); i++)
    {
        if (presieve[i])
        {
            primes.push_back(2 * i + 3);
        }
    }
    std::reverse(primes.begin(), primes.end());
    start = sqrtn;
    uint num_threads = std::thread::hardware_concurrency() * 2;
    std::vector<std::thread> threads;
    for (uint i = 0; i < num_threads; ++i)
    {
        threads.push_back(std::thread(segmented_sieve_worker, std::ref(primes)));
    }
    while (start < num - sqrtn)
    {
        std::cout << "\r" << start / sqrtn << "/" << sqrtn;
        usleep(10000);
    }
    std::for_each(threads.begin(), threads.end(), [](std::thread &t)
                  { t.join(); });
    std::cout << std::endl;
    return 0;
}

long long difference(std::chrono::system_clock::time_point start)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() -
           std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();
}

std::vector<bool> basic_wrapper(ulong lnum)
{
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::cout << "start sieve" << std::endl;
    ulong num = (lnum - 1) / 2;
    std::vector<bool> primes(num, true);
    ulong limit = (sqrt(2 * num + 3) - 1) / 2;
    basic_sieve(num, limit, primes);
    std::cout << "sieve took  " << difference(start) << "ms" << std::endl;
    return primes;
}

void basic_sieve(ulong &num, ulong &limit, std::vector<bool> &primes)
{
    for (ulong i = 0; i < limit; ++i)
    {
        if (primes[i])
        {
            for (ulong j = ((2 * i + 3) * (2 * i + 3) - 3) / 2; j <= num; j += 2 * i + 3)
            {
                primes[j] = false;
            }
        }
    }
}

/**
 * @brief A segmented sieve between two numbers.
 * @param start The value to start at
 * @param end The value to end at
 * @param foundprimes A std::vector containing all primes up to \f$\sqrt{end}\f$, in reverse order
 * @return std::vector<bool> A std::vector dictation whether each odd number is prime.
 */
void segmented_sieve(ulong start, ulong end, std::vector<ulong> foundprimes)
{
    // First establish the actual start and end
    ulong st, en;
    if ((start & 1) == 1)
        st = start;
    else
        st = start + 1;
    if ((end & 1) == 1)
        en = end;
    else
        en = end - 1;
    ulong const num = (en - st) / 2 + 1;
#ifdef DEBUG
    std::cout << st << std::endl;
    std::cout << en << std::endl;
#endif
    // create dynamic_bitset
    boost::dynamic_bitset<unsigned char, std::allocator<unsigned char>> bitset(num);
    // make it true
    bitset.set();
    for (ulong prime : foundprimes)
    {
        ulong square = prime * prime;
        if (square > en)
        {
            // no relevant multiples in this range.
            continue;
        }
        else
        {
            ulong j;
            if (st >= square)
            {
                // Slightly weird method of finding start
                j = prime * (ulong) ceil(st / (double)prime) - st;
                if (j & 0b0001)
                {
                    j += prime;
                }
                j /= 2;
            }
            else
            {
                j = (square - st) / 2;
            }
            while (j < num)
            {
                bitset.set(j, false);
                j += prime;
            }
        }
    }
    std::string filename = "./primesfolder/" + std::to_string(st) + "." + std::to_string(en) + ".primes";
    std::ofstream file(filename);
    std::string str = "";
#ifndef BINARY
    boost::to_string(bitset, str);
    file << str;
#endif
#ifdef DEBUG
    file << "\n";
    for (ulong i = 0; i < bitset.size(); ++i)
    {
        if (bitset[i])
        {
            file << std::to_string(2 * i + st);
        }
    }
    file << "\n";
#endif
#if defined(DEBUG) || defined(BINARY)
    str = "";
    std::for_each(bitset.m_bits.begin(), bitset.m_bits.end(), [&str](unsigned char &c){str += c;});
    file << str;
#endif
    file.close();
}

int segmented_sieve_worker(std::vector<ulong> &primes)
{
    work_mutex.lock();
    while (start <= num - sqrtn)
    {
        std::thread workthread(segmented_sieve, start, start + sqrtn, primes);
        start += sqrtn;
        work_mutex.unlock();
        workthread.join();
        work_mutex.lock();
    }
    work_mutex.unlock();
    return 0;
}
