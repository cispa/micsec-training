all: cache_measure

cache_measure: cache_measure.c
	gcc cache_measure.c -O3 -Wall -o cache_measure

solution: solution.c
	gcc solution.c -O3 -Wall -o solution

clean:
	rm -f cache_measure solution
