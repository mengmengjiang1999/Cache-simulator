//
// Created by chenzm on 2020/4/7.
//

#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H


#include "policy_lru.h"
#include "policy_plru.h"
#include "policy_random.h"

#define ADDR_LEN 64

class Cache{
    uint32_t cache_size_;//kb
    uint32_t block_size_;//b
    uint32_t block_offset_;
    uint32_t way_;//表示映射方式，way=0:全相联，way=1:直接映射
    uint32_t group_;//一共有多少组
    uint32_t group_bit_;//index有多少位
    uint32_t flag_;
    POLICY replace_policy_;
    bool is_Write_Alloc_;
    bool is_Write_Through_;

    replacement_policy* replacementPolicy;
    uint64_t* data_;


    void init_policy();
    void init_alloc();

    //此函数封装了位运算，含义是取出64位的addr中，从右往左数第right位开始截取length位
    uint64_t get_some_bits(uint64_t addr, uint64_t right,uint64_t length);

    //处理器给cache一个地址后，取出它在哪个组
    uint64_t get_group(uint64_t addr);

    //处理器给cache一个地址后，取出它的标签位
    uint64_t get_flag(uint64_t addr);

    //cache中存储的数据中取出标签位
    uint64_t get_flag_from_data(uint64_t data);
    //cache中存储的数据判断这是否为可用数据
    bool is_valid_data(uint64_t data);
    //判断数据是否为dirty（在写回策略时使用，用于告诉主存这里有个数据要flush进来
    bool is_dirty_data(uint64_t data);

    //取出块内位移，不过在本次实验当中似乎没有用到
    uint64_t get_block_offset(uint64_t addr);

    //想把addr存储到cache里面时应该存进去什么
    uint64_t store_data(uint64_t addr);

    //用于输出addr的二进制
    void outputbin(uint64_t addr);

public:
    Cache(uint32_t cache_size, uint32_t block_size,
            uint32_t way, POLICY replace_policy,
            bool is_write_alloc):
            cache_size_(cache_size),block_size_(block_size),
            way_(way),replace_policy_(replace_policy),
            is_Write_Alloc_(is_write_alloc){
        assert(way_==0||way_==1||way_==2||way_==4||way_==8);
        if(way_ == 0)way_=(cache_size_<<10)/(block_size_);//way = 0表示全相联，这里计算一下它到底是多少路
        group_ = (cache_size_<<10)/(block_size_*way_);//组数=cache容量/(块大小*每组当中的块数)
        group_bit_ = uint32_t(ceil(log(group_)/log(2)));//组数需要多少位来表示
        block_offset_ = uint32_t(ceil(log(block_size_)/log(2)));//计算块内位移所占的大小
        flag_ = ADDR_LEN - group_bit_ - block_offset_;//标签位=地址长度-组数-块内位移
        assert(flag_ + 2<=ADDR_LEN);
        init_policy();
        init_alloc();
#ifdef DEBUG
        cout<<"Cache constructing..."<<endl;
        cout<<"cache size = "<<cache_size<<endl;
        cout<<"block size = "<<block_size<<endl;
        cout<<"way number = "<<way_<<endl;
        cout<<"group number = "<<group_<<endl;
        cout<<"group bit = "<<group_bit_<<endl;
        cout<<"block offset = "<<block_offset_<<endl;
        cout<<"flag length = "<<flag_<<endl;
        cout<<"is write alloc = "<<is_Write_Alloc_<<endl;
        cout<<"policy is "<<replace_policy_<<endl;
#endif
    }
    bool data_read(uint64_t addr);
    bool data_write(uint64_t addr);

};
#endif //CACHE_CACHE_H
