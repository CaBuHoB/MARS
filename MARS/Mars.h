#ifndef LAB_2_MARS_H
#define LAB_2_MARS_H

#include <array>
#include <vector>


class MARS {
private:
    std::array<unsigned, 40> K;
    std::array<unsigned, 512> S;

    void setKey(const std::vector<unsigned> &key);

    std::tuple<unsigned, unsigned, unsigned> e_func(const unsigned &in, const unsigned &key1, const unsigned &key2);

    void f_mix(unsigned &a, unsigned &b, unsigned &c, unsigned &d);

    void b_mix(unsigned &a, unsigned &b, unsigned &c, unsigned &d);

    void f_trans(unsigned &a, unsigned &b, unsigned &c, unsigned &d, unsigned i);

    void r_trans(unsigned &a, unsigned &b, unsigned &c, unsigned &d, unsigned i);

    unsigned makeMask(unsigned x);

public:
    MARS();

    std::array<unsigned, 4> encrypt(const std::array<unsigned, 4> &inBlock, const std::vector<unsigned> &key);

    std::array<unsigned, 4> decrypt(const std::array<unsigned, 4> &inBlock, const std::vector<unsigned> &key);

    std::vector<unsigned> getRandomKey();

};


#endif
