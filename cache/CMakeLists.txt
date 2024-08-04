cmake_minimum_required(VERSION 3.12)
project(cache)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cache
        cache.cpp
        cache.h
        main.cpp
        policy_lru.h
        policy_mru.h
        policy_node.h
        policy_plru.h
        policy_random.h
        replacement_policy.h
        replacement_policy.cpp)
