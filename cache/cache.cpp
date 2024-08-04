//
// Created by chenzm on 2020/4/7.
//

#include "cache.h"
#include "replacement_policy.h"
#include "policy_node.h"
#include "policy_random.h"
#include "policy_plru.h"
#include "policy_lru.h"

void Cache::init_policy(){
    switch (replace_policy_){
        case P_LRU:
            replacementPolicy = new policy_lru(cache_size_,
                                               ((cache_size_<<10)/(way_*block_size_)),
                                               way_,
                                               replace_policy_);
            break;
        case P_PLRU:
            replacementPolicy = new policy_plru(cache_size_,
                                                ((cache_size_<<10)/(way_*block_size_)),
                                                way_,
                                                replace_policy_);
            break;
        case P_RANDOM:
            replacementPolicy = new policy_random(cache_size_,
                                                  ((cache_size_<<10)/(way_*block_size_)),
                                                  way_,
                                                  replace_policy_);
            break;
        default:
            cout<<"invalid replacement policy..."<<endl;
            break;
    }
}

void Cache::init_alloc() {
    data_ = new uint64_t[group_*way_];
}

uint64_t Cache::get_some_bits(uint64_t addr, uint64_t right, uint64_t length) {
    return uint64_t((addr>>right)&uint64_t((uint64_t (1)<<length)-1));
}

uint64_t Cache::get_group(uint64_t addr) {
    return get_some_bits(addr, block_offset_, group_bit_);
}

uint64_t Cache::get_flag(uint64_t addr) {
    return get_some_bits(addr, block_offset_+group_bit_, flag_);
}

uint64_t Cache::get_flag_from_data(uint64_t data) {
    return get_some_bits(data, 0, flag_);
}

bool Cache::is_dirty_data(uint64_t data) {
    return bool(get_some_bits(data,flag_+1,1));
}

bool Cache::is_valid_data(uint64_t data) {
    return bool(get_some_bits(data,flag_,1));
}

uint64_t Cache::get_block_offset(uint64_t addr) {
    return get_some_bits(addr,0,block_offset_);
}

uint64_t Cache::store_data(uint64_t addr) {
    uint64_t flag = get_flag(addr);
//    outputbin(flag);
    uint64_t data = flag;
    data |= uint64_t(uint64_t (1)<<(flag_));//is valid
    data |= uint64_t(uint64_t (1)<<(flag_+1));//is dirty
    return data;
}

void Cache::outputbin(uint64_t addr) {
    cout<<bitset<sizeof(uint64_t) * 8>(addr)<<endl;
}

bool Cache::data_read(uint64_t addr) {
#ifdef DEBUG
    cout<<"data reading...."<<endl<<bitset<sizeof(uint64_t) * 8>(addr)<<endl;
#endif
    uint32_t index = get_group(addr);
    bool b= false;
    //标签比对
    for(uint32_t i = 0;i < way_;i++){
        uint64_t r = data_[index * way_ + i];
        if(is_valid_data(r)
            && get_flag_from_data(r) == get_flag(addr)){
            b = true;
            replacementPolicy->visited(index,i);
            break;
        }
    }
    if(!b){
        //没有命中，就要更新cache了
#ifdef DEBUG
        cout<<"int cache updating..."<<endl;
#endif
        uint32_t vic  = way_;

        for(int j=0;j<way_;j++){
            uint64_t r = data_[index * way_ + j];
            if(!is_valid_data(r)){
                vic = j;
            }
        }
        if(vic == way_)vic = replacementPolicy->get_victim(index);
#ifdef DEBUG
        cout<<"victim is..."<<vic<<endl;
#endif
        data_[index* way_ + vic] = store_data(addr);
#ifdef DEBUG
        cout<<"data stored is..."<<endl;outputbin(data_[index* way_ + vic]);
#endif
        replacementPolicy->visited(index,vic);
    }
    return b;
    //返回是否命中
}

//todo:写直达和写回我不知道会对读写操作产生什么影响，所以暂时就都当它是写直达了
bool Cache::data_write(uint64_t addr) {
//    cout<<"data writing..."<<endl<<bitset<sizeof(uint64_t) * 8>(addr)<<endl;
    uint32_t index = get_group(addr);
    bool b= false;
    //标签比对
    for(uint32_t i = 0;i < way_;i++){
        uint64_t r = data_[index * way_ + i];
        if(is_valid_data(r)
           && get_flag_from_data(r) == get_flag(addr)){
            b = true;
            replacementPolicy->visited(index,i);
            break;
        }
    }
    if(!b){
        //没有命中，就要更新cache了
        if(is_Write_Alloc_){
            uint32_t vic  = way_;

            for(int j=0;j<way_;j++){
                uint64_t r = data_[index * way_ + j];
                if(!is_valid_data(r)){
                    vic = j;
                }
            }
            if(vic == way_ )vic = replacementPolicy->get_victim(index);
            data_[index* way_ + vic] = store_data(addr);
            replacementPolicy->visited(index,vic);
        }
    }
    return b;
}