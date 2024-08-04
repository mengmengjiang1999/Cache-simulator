//
// Created by chenzm on 2020/4/7.
//

#ifndef CACHE_POLICY_PLRU_H
#define CACHE_POLICY_PLRU_H


#include "replacement_policy.h"
#include "policy_node.h"

using namespace std;

static uint32_t tway_plru;//共有多少路
static uint32_t tlogway_plru;//log之后向上取整有几位

class plru_tree : public policy_node{
    uint8_t* bin;

    /*
     * 从低位到高位为0～7
     */
    bool get_bit(uint32_t pos){
        assert(pos<tway_plru&&pos>=0);
        return (bin[pos/8]>>(pos%8))&uint8_t(1);
    }

    /*
     * pos:bit的位置
     * b：希望修改为什么
     */
    uint32_t put_bit(uint32_t pos, bool b){
        if(b){
            bin[pos/8] |= uint8_t(1)<<(pos%8);
        } else{
            bin[pos/8] &= (~(uint8_t(1)<<(pos%8)));
        }
        return 0;
    }

public:
    plru_tree(){
        uint32_t len = (tway_plru - 1 + 7)/8;
        bin = new uint8_t[len];
    }

    ~plru_tree(){
        delete [] bin;
    }

    uint32_t get_victim() override {
        uint32_t pos = 0, cal = 0;
        for(uint32_t i = 0; i< tlogway_plru;i ++){
            bool b = get_bit(pos);
            if(b){
                cal += (1 << (tlogway_plru - 1 - i));
                pos = (pos<<1) + 2;
            } else{
                pos = (pos<<1) + 1;
            }
        }
        return cal;
    }

    void visit(uint32_t t) override {
        assert(t<tway_plru&&t>=0);
        uint32_t pos=0;
        for(uint32_t i = 0;i<tlogway_plru;i++){
            bool b = (t >> (tlogway_plru -1 - i))&uint8_t(1);
            if(b){
                put_bit(pos, false);
                pos = (pos << 1) + 2;
            } else{
                put_bit(pos, true);
                pos = (pos << 1) + 1;
            }
        }
    }
};

class policy_plru: public replacement_policy{
    plru_tree* t;
    void init_policy(){
        tway_plru = way_;
        tlogway_plru = uint32_t(ceil(log(way_)/log(2)));
        t = new plru_tree[group_];
    }

public:
    policy_plru(uint32_t cache_size,
                uint32_t group,uint32_t way, POLICY policy):
                replacement_policy(cache_size, group,way, policy){
        init_policy();
    }

    ~policy_plru() override{
        delete []t;
    }

    uint32_t get_victim(uint32_t group) override {
        return t[group].get_victim();
    }

    void visited(uint32_t group,uint32_t node) override{
        t[group].visit(node);
    }
};

#endif //CACHE_POLICY_PLRU_H
