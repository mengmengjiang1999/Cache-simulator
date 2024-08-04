
#include <assert.h>
#include <iostream>
#include "cmath"
using namespace std;

uint32_t way_;//共有多少路
uint32_t logway_;//log之后向上取整有几位

class lru_stack{
    uint8_t * stack;

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
//        bianli_bin();
    }
public:
    /*
     * 返回第num个位置对应的数
     * 需要取出第logway_*num到(logway_+1)*num-1这么多个bit位
     * 下标对应的是num*logway_/8
     * 需要验证一下
     */
    uint32_t get(uint32_t num){
        uint32_t store=0;
        uint32_t cnt=logway_*num;
        for(int i=0;i<logway_;i++){
            store += (get_bit(cnt+i)<<i);
        }
        return store;
    }


    /*
     * num:希望修改的是num个位置为t
     * t：希望修改为t
     */
    uint32_t put(uint32_t num, uint32_t t){
        assert(t<=way_);
        assert(num<=way_);
        uint32_t tmp=t;
        int cnt=logway_*num;
        int move=logway_*num%8;
        for(int i=0;i<logway_;i++){
            put_bit(cnt+i,bool(tmp&uint8_t(1)));
            tmp=tmp>>1;
        }
    }

    lru_stack()
    {
        uint32_t len = way_*logway_/8;
        if(len == 0)len=1;
        stack = new uint8_t[len];
    }
    uint32_t get_victim(){
        return get(way_-1);
    }
    uint32_t visit(uint32_t v){

        uint32_t v_=0;
        for(uint32_t i=0;i<way_;i++){
            if(get(i)==v){
                v_=i;
                break;
            }
        }
        for(uint32_t j=v_;j>0;j--){
            put(j,get(j-1));
        }
        put(0,v);
        return 0;
    }
    void bianli(){
        for(int i=0;i<way_;i++){
            cout<<get(i)<<" ";
        }cout<<endl;
    }
    void bianli_bin() {
        for (int i = 0; i < way_ * logway_ / 8; i++) {
//            cout<<hex<<stack[i]<<" ";
            cout << bitset<sizeof(uint8_t) * 8>(stack[i])<<" ";
        }
        cout << endl;
    }
    void bianli_bit(){
        for(int i= 0;i< way_*logway_;i++){
            cout<<get_bit(i);
            if((i+1)%8==0)cout<<" ";
        }cout<<endl;
    }

};

lru_stack s;
int main() {
    way_ = 7; logway_ = uint32_t(ceil(log(way_)/log(2)));
    cout<<way_<<" "<<logway_<<endl;
    for(int i = 0; i< 8 ; i++){
        s.put(i,i);cout<<s.get(i)<<endl;
        s.bianli_bin();
        s.bianli_bit();
    }
    s.bianli();
    s.bianli_bin();
    for(int i=0;i<8;i++){
        int t= rand()%way_;
        cout<<t<<endl;
        s.put(i,t);
        s.bianli();
        s.bianli_bin();
        assert(t==s.get(i));
    }cout<<endl;
    for(int i = 0; i< 8 ; i++){
        s.put(i,i);cout<<s.get(i)<<endl;
    }
    for(int i=0;i<200;i++){
        int t=rand()%way_;
        cout<<"visiting "<<t<<" ";
        s.visit(t);
        s.bianli();
        cout<<"victim is "<<s.get_victim()<<endl;
//        assert(s.get_victim() == t);
    }
    return 0;
}