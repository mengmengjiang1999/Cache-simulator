//
// Created by chenzm on 2020/4/8.
//

#ifndef CACHE_POLICY_NODE_H
#define CACHE_POLICY_NODE_H

#include <cstdint>

class policy_node{
public:
    virtual uint32_t get_victim() = 0;//返回被替换的是哪个
    virtual void visit(uint32_t v) = 0;//访问了哪个节点
};

#endif //CACHE_POLICY_NODE_H
