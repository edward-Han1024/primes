## bits and bytes
bits are 1-7, bytes start at 0.
## structure
offsets mod 30:

1
7
11
13
17
19
23
29
1     29 31    59 61   ...
01111111 11111111 11111...
 ^
 bit here is 7, set to 0
1     29 31    59 61   ...
00111111 11111111 11111...
              ^
              bit here is 49, start here and sieve
1     29 31    59 61    89 91   119
00111111 11111011 11111111 11111111
                      ^ bit here is 77, 0;
1     29 31    59 61    89 91   119 121  149 151  179 181  209 211 ...
00111111 11111011 11110111 11111111 11111111 11111111 11111111 1111...
              ^            ^ 91   ^ 119^ 133   ^ 161        ^ 203
## tables
If the prime is 1 mod 30 and in the nth byte, then the multiple are in
byte ... and bit ...
     n           1
	 7n          2
	 11n         3
	 13n         4
	 17n         5
	 19n         6
	 23n         7
	 29n         8
  >>>31n+1       1<<<
	 37n+1       2
	 ...         ...
prime is 7 mod 30 and in the nth byte...
byte ... and bit ...
     n           2
	 7n+1        6
	 11n+2       5
	 13n+3       1
	 17n+3       8
	 19n+4       4
	 23n+5       3
	 29n+6       7
  >>>31n+7       2<<<
     37n+8       6
prime is 11 mod 30 and in the nth byte...
byte ... and bit ...
     n           3
	 7n+2        5
	 11n+4       1
	 13n+4       7
	 17n+6       2
	 19n+6       8
	 23n+8       4
	 29n+10      6
  >>>31n+11      3<<<
     37n+13      5
prime is 13 mod 30 and in the nth byte...
     n           4
	 7n+3        1
	 11n+4       7
	 13n+5       6
	 17n+7       3
	 19n+8       2
	 23n+9       8
	 29n+12      5
  >>>31n+13      4<<<
     37n+16      1
prime is 17 mod 30 and in the nth byte...
     n           5
	 7n+3        8
	 11n+6       2
	 13n+7       3
	 17n+9       6
	 19n+10      7
	 23n+13      1
	 29n+16      4
  >>>31n+17      5<<<
     37n+20      8
prime is 19 mod 30 and in the nth byte...
     n           6
	 7n+4        4
	 11n+6       8
	 13n+8       2
	 17n+10      7
	 19n+12      1
	 23n+14      5
	 29n+18      3
  >>>31n+19      6<<<
     37n+23      4
prime is 23 mod 30 and in the nth byte...
