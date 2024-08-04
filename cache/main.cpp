#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include "replacement_policy.h"
#include "cache.h"

using namespace std;
//设计一个读写命令行
/*
 *　./main cache_size block_size way policy is_write_alloc is_write_through
 */

extern Cache cache;

void output(char* filename, uint32_t cache_size, uint32_t block_size, uint32_t way,
        char* policy, bool is_write_alloc, bool is_write_through,
        uint32_t hit,uint32_t miss){
    cout<<"=============================================="<<endl;
    cout<<"filename = "<<filename<<endl;
    cout<<"cache size = "<<cache_size<<endl;
    cout<<"block size = "<<block_size<<endl;
    cout<<"way = "<<way<<endl;
    cout<<"policy = "<<policy<<endl;
    if(is_write_alloc)cout<<"write alloc ";
    else cout<<"write no alloc";
    if(is_write_through)cout<<"write through"<<endl;
    else cout<<"write back"<<endl;
    cout<<"hit = "<<hit<<" miss = "<<miss<<endl;
    cout<<"miss rate = "<< (miss + 0.0)/(miss+hit) << endl;
    cout<<"=============================================="<<endl;
}

int main(int argc,char* argv[]) {
    assert(argc == 8||argc == 9);
    uint32_t cache_size=atoi(argv[1]);
    uint32_t block_size=atoi(argv[2]);
    uint32_t way=atoi(argv[3]);
    POLICY policy;
    if(strcmp(argv[4],"P_LRU")==0){
        policy = P_LRU;
    } else if(strcmp(argv[4],"P_PLRU")==0){
        policy = P_PLRU;
    } else if(strcmp(argv[4],"P_RANDOM")==0){
        policy = P_RANDOM;
    }

    assert(policy==P_RANDOM || policy == P_LRU || policy == P_PLRU);

    uint32_t a5 = atoi(argv[5]);
    assert(a5 == 0 || a5 == 1);
    bool is_write_alloc = bool(a5);

    uint32_t a6 = atoi(argv[6]);
    assert(a6 == 0 || a6 == 1);
    bool is_write_through = bool(a6);


    Cache cache(cache_size,block_size,way,policy,is_write_alloc);

    string filename = argv[7];

    FILE *fp = freopen(argv[7], "r", stdin);

    uint32_t cnt=0;
    uint32_t hit=0;
    uint32_t miss=0;

    char opr;

    uint64_t addr;

    while(cin >> opr >> hex >> addr){
        bool b= false;
        if(opr == 'r'){
            b = cache.data_read(addr);
        } else if(opr == 'w'){
            b = cache.data_write(addr);
        } else{
            cout<<"I don't know how to operate. "<<endl;
        }
        if(b){
            hit++;
        } else{
            miss++;
        }
        cnt++;
    }


    char outfilename[] = "test4.log";
    if(argc == 9)strcpy(outfilename,argv[8]);
    FILE *fw = freopen(outfilename, "a", stdout);

    output(argv[7],cache_size,block_size,way,argv[4],
            is_write_alloc,is_write_through,
            hit,miss);

    fclose(fp);

    fclose(fw);
    return 0;
}