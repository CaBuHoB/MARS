#ifndef LAB_2_MARS_H
#define LAB_2_MARS_H

#include <array>
#include <vector>

using DWORD = unsigned long;
using BYTE = unsigned char;

class MARS {
private:
    std::array<DWORD, 40> K{};
    DWORD S[512];

    DWORD mod;

    void setKey(const std::vector<DWORD> &key);

    std::tuple<DWORD, DWORD, DWORD> e_func(const DWORD &in, const DWORD &key1, const DWORD &key2);

    void f_mix(DWORD &a, DWORD &b, DWORD &c, DWORD &d);

    void b_mix(DWORD &a, DWORD &b, DWORD &c, DWORD &d);

    void f_trans(DWORD &a, DWORD &b, DWORD &c, DWORD &d, DWORD i);

    void r_trans(DWORD &a, DWORD &b, DWORD &c, DWORD &d, DWORD i);

    DWORD makeMask(DWORD x);

public:
    MARS();

    std::array<DWORD, 4> encrypt(const std::array<DWORD, 4> &inBlock, const std::vector<DWORD> &key);

    std::array<DWORD, 4> decrypt(const std::array<DWORD, 4> &inBlock, const std::vector<DWORD> &key);

    std::vector<DWORD> getRandomKey();

};


#endif
