# THUOOP @ 20200129
# C++ Course for THU2020 on Linux
#
.PHONY:clean
FLAG=$(empty) $(empty)
all:main
main:main.o cache.o replacement_policy.o cache.h policy_lru.h policy_node.h policy_mru.h policy_plru.h policy_random.h replacement_policy.h
	g++ main.o cache.o replacement_policy.o -o main -std=c++11

cache.o:cache.cpp replacement_policy.cpp cache.h policy_lru.h policy_node.h policy_mru.h policy_plru.h policy_random.h replacement_policy.h
	g++ -c cache.cpp -o cache.o -std=c++11

replacement_policy.o:replacement_policy.cpp replacement_policy.h policy_node.h
	g++ -c replacement_policy.cpp -o replacement_policy.o -std=c++11

main.o:main.cpp cache.h policy_lru.h policy_node.h policy_mru.h policy_plru.h policy_random.h replacement_policy.h
	g++ -c main.cpp -o main.o -std=c++11

clean:
	rm main *.o