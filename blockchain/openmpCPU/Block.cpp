//
// Created by Dave Nash on 20/10/2017.
//

#include "Block.h"
#include "sha256.h"
#include "omp.h"

Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn)
{
    _nNonce = 0;
    _tTime = time(nullptr);

    sHash = _CalculateHash(0);
}

void Block::MineBlock(uint32_t nDifficulty)
{
    char cstr[nDifficulty + 1];
    for (uint32_t i = 0; i < nDifficulty; ++i)
    {
        cstr[i] = '0';
    }
    cstr[nDifficulty] = '\0';

    string str(cstr);

    bool found = false;
    #pragma omp parallel shared(found)
    {
    int threads = omp_get_num_threads();
    uint32_t privateNounce = (uint32_t) omp_get_thread_num();
    string privatesHash;
    while(!found)
    {
         
        privateNounce += threads;
        privatesHash = _CalculateHash(privateNounce);
        if(privatesHash.substr(0, nDifficulty) == str){
            #pragma omp critical
            {
            sHash = privatesHash;
            found = true;
            }
        }
    }
    }
    cout << "Block mined: " << sHash << endl;
}

inline string Block::_CalculateHash(uint32_t privatenNonce) const
{
    stringstream ss;
    ss << _nIndex << sPrevHash << _tTime << _sData << privatenNonce;

    return sha256(ss.str());
}
