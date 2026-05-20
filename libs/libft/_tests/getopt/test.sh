#!/bin/bash

make -C ../.. &&
	cc test.c -I ../../incs -L ../.. -lft -o og -g3 -fsanitize=address &&
	cc test.c -I ../../incs -L ../.. -lft -o ft -g3 -DFT -fsanitize=address &&
	diff <(./og $@) <(./ft $@) --side-by-side --color=always
