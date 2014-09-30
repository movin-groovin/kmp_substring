


all: program


program: kmp_algo.o
	@g++ kmp_algo.o -o kmp_algo

kmp_algo.o: kmp_algo.cpp
	@g++ -std=c++11 kmp_algo.cpp -c


clean:
	@rm -f kmp_algo.o
