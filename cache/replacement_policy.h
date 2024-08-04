//
// Created by chenzm on 2020/4/7.
//

#ifndef CACHE_REPLACEMENT_POLICY_H
#define CACHE_REPLACEMENT_POLICY_H

//#define DEBUG

#include <cstdint>
#include <assert.h>
#include <iostream>
#include "cmath"

#include "policy_node.h"

enum POLICY{
    P_LRU,
    P_PLRU,
    P_RANDOM
};

class replacement_policy{
protected:

    uint32_t cache_size_;
    uint32_t group_;
    uint32_t way_;
    POLICY policy_;

//    virtual void init_policy(){}

public:
    replacement_policy(uint32_t cache_size,
            uint32_t group,uint32_t way, POLICY policy):
            cache_size_(cache_size),group_(group),
            way_(way),policy_(policy)
            {
    }

    virtual ~replacement_policy() = 0;

    virtual uint32_t get_victim(uint32_t group) = 0;
    virtual void visited(uint32_t group,uint32_t node) = 0;

};
#endif //CACHE_REPLACEMENT_POLICY_H
