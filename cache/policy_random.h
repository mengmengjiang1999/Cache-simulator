//
// Created by chenzm on 2020/4/7.
//

#ifndef CACHE_POLICY_RANDOM_H
#define CACHE_POLICY_RANDOM_H

#include "replacement_policy.h"
#include <random>
using namespace std;

class policy_random: public replacement_policy{

    void init_policy(){}

public:
    policy_random(uint32_t cache_size, uint32_t group,
            uint32_t way, POLICY policy):
            replacement_policy(cache_size,group, way, policy){

    }
    ~policy_random() override{

    }

    uint32_t get_victim(uint32_t group) override{
        uint32_t r = rand()%way_;
        return r;
    }

    void visited(uint32_t group,uint32_t node) override{

    }

};

#endif //CACHE_POLICY_RANDOM_H
