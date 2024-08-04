//
// Created by chenzm on 2020/4/7.
//

#ifndef CACHE_POLICY_LRU_H
#define CACHE_POLICY_LRU_H


#include "replacement_policy.h"
#include "policy_node.h"

using namespace std;

static uint32_t tway_;//共有多少路
static uint32_t tlogway_;//log之后向上取整有几位

class lru_stack: public policy_node{
    uint8_t* stack;

    /*
     * 返回第pos个bit的值
     */
    bool get_bit(uint32_t pos){
        return (stack[pos/8]>>(pos%8)) & uint8_t(1);
    }

    /*
     * pos:bit的位置
     * b：希望修改为什么
     */
    uint32_t put_bit(uint32_t pos, bool b){
        if(b){
            stack[pos/8] |= uint8_t(1)<<(pos%8);
        } else{
            stack[pos/8] &= (~(uint8_t(1)<<(pos%8)));
        }
        return 0;
    }

    /*
     * 返回第num个位置对应的数
     * 需要取出第logway_*num到(logway_+1)*num-1这么多个bit位
     * 下标对应的是num*logway_/8
     * 需要验证一下
     */
    uint32_t get(uint32_t num){
        uint32_t store=0;
        uint32_t cnt=tlogway_*num;
        for(int i=0;i<tlogway_;i++){
            store += (get_bit(cnt+i)<<i);
        }
        return store;
    }


    /*
     * num:希望修改的是num个位置为t
     * t：希望修改为t
     */
    uint32_t put(uint32_t num, uint32_t t){
        assert(t<=tway_);
        assert(num<=tway_);
        uint32_t tmp=t;
        int cnt=tlogway_*num;
        int move=tlogway_*num%8;
        for(int i=0;i<tlogway_;i++){
            put_bit(cnt+i,bool(tmp&uint8_t(1)));
            tmp=tmp>>1;
        }
        return 0;
    }

public:
    lru_stack()
    {
        uint32_t len = (tway_ * tlogway_ +7)/8;
        stack = new uint8_t[len];
        for(int i=0;i<tway_;i++){
            put(i,i);
        }
    }

    ~lru_stack(){
        delete [] stack;
    }
    uint32_t get_victim() override{
        return get(tway_-1);
    }
    void visit(uint32_t v) override{
        uint32_t v_=0;
        for(uint32_t i=0;i<tway_;i++){
            if(get(i)==v){
                v_=i;
                break;
            }
        }
        for(uint32_t j=v_;j>0;j--){
            put(j,get(j-1));
        }
        put(0,v);
    }

#ifdef DEBUG
    void bianli(){
        for(int i=0;i<tway_;i++){
            cout<<get(i)<<" ";
        }cout<<endl;
    }
    void bianli_bin() {
        for (int i = 0; i < tway_ * tlogway_ / 8; i++) {
            cout << bitset<sizeof(uint8_t) * 8>(stack[i])<<" ";
        }
        cout << endl;
    }
    void bianli_bit(){
        for(int i= 0;i< tway_*tlogway_;i++){
            cout<<get_bit(i);
            if((i+1)%8==0)cout<<" ";
        }cout<<endl;
    }

#endif

};

class policy_lru  : public replacement_policy{
    lru_stack* s;

    void init_policy(){
        tway_ = way_; tlogway_ = uint32_t(ceil(log(way_)/log(2)));
#ifdef DEBUG
        cout<<"tway_ = "<<tway_<<" tlogway_ = "<<tlogway_<<endl;
#endif
        s = new lru_stack[group_];
    }


public:
    policy_lru(uint32_t cache_size, uint32_t group,
               uint32_t way, POLICY policy)
               :replacement_policy
               (cache_size, group,way, policy){
        init_policy();
    }

    ~policy_lru() override{
        delete []s;
    }

    /*
     * 返回被替换掉的是哪个
     */
    uint32_t get_victim(uint32_t group) override{
        return s[group].get_victim();
    }

    /*
     * 刚刚第group组的第node个数据被访问过了
     */
    void visited(uint32_t group,uint32_t node) override{
        s[group].visit(node);
    }

};

#endif //CACHE_POLICY_LRU_H
