//
// Created by maxim on 02/10/18.
//

#ifndef LAB_2_MARS_H
#define LAB_2_MARS_H

#include <array>
#include <lcms.h>
#include <vector>

class MARS {
private:
    std::array<DWORD, 4> D;
    std::array<DWORD, 40> K{}; // keys

    DWORD S[512]; // S-box
    DWORD *S0;
    DWORD *S1;

    DWORD mod;

    DWORD makeMask(const DWORD &w);

    void keyGeneration(const std::vector<DWORD> &key);

    DWORD circularShiftsR(const DWORD &D, const size_t &count);

    DWORD circularShiftsL(const DWORD &D, const size_t &count);

    void forwardMode(const unsigned int &roundNumber);

    void backwardsMode(const unsigned int &roundNumber);

    void directMixingRound();

    void forwardMixing();

    std::tuple<DWORD, DWORD, DWORD> E_function(const DWORD &D, const DWORD &key1, const DWORD &key2);

    void cryptographicCore();

    void reverseMixingRound();

    void backwardsMixing();

public:
    explicit MARS();

    std::array<DWORD, 4> getCiphertext(const std::vector<DWORD> &D, const std::vector<DWORD> &key);

    std::array<DWORD, 4> getEncrypted(const std::vector<DWORD> &D, const std::vector<DWORD> &key);

};


#endif //LAB_2_MARS_H
