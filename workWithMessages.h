#include <iterator>
#include <bitset>
#include <vector>
#include <lcms.h>
#include <iostream>

std::vector<DWORD> stringToDWORDmas(const std::string &str) {
    std::vector<DWORD> arr;
    DWORD num = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (i != 0 and i % 4 == 0) {
            arr.push_back(num);
            num = 0;
        }
        num = num | (BYTE(str[i]) << ((i % 4) * 8));
    }
    arr.push_back(num);

    for (int i = 0; i < (arr.size() % 4); ++i)
        arr.push_back(0);

    return arr;
}

std::string masDWORDtoString(const std::vector<DWORD> &arr) {
    std::string str;
    for (const auto num : arr) {
        for (int i = 0; i < 4; ++i) {
            BYTE symb = static_cast<BYTE>(num >> (i * 8));
            if (symb)
                str += char(symb);
        }
    }

    return str;
}

std::string getBits(const std::vector<DWORD> &arr){
    std::string arrBits;
    for(const auto dword : arr){
        std::bitset<32> bits (dword);
        arrBits += bits.to_string();
    }

    return arrBits;
}

void distribution(const std::vector<DWORD> &encrypt){
    std::string encBits = getBits(encrypt);

    DWORD col = 0;
    for(auto bit : encBits) {
        if (bit == '0')
            col++;
    }
    std::cout << "Number of zeros: " << col << " " << col * 1.0 / encBits.length() * 100 << "%\n";
    std::cout << "Number of units: " << encBits.length() - col << " ";
    std::cout << (encBits.length() - col) * 1.0 / encBits.length() * 100 << "%\n";
}

void corrCoef (const std::vector<DWORD> &encrypt, const std::vector<DWORD> &decrypt){
    std::string encBits = getBits(encrypt);
    std::string decBits = getBits(decrypt);

    double _x = 0;
    for(const auto bit : encBits)
        _x += static_cast<DWORD> (bit);
    _x /= encBits.length();

    double _y = 0;
    for(const auto bit : decBits)
        _y += static_cast<DWORD> (bit);
    _y /= decBits.length();

    double numerator = 0;
    for(int i=0; i< encBits.length();++i)
        numerator += (static_cast<DWORD> (encBits[i]) - _x) * (static_cast<DWORD> (decBits[i]) - _y);

    double denominator = 0;
    double denominatorLeft = 0;
    for (char encBit : encBits)
        denominatorLeft += (static_cast<double> (encBit) - _x) * (static_cast<double> (encBit) - _x);
    double denominatorRight = 0;
    for (char decBit : decBits)
        denominatorRight += (static_cast<double> (decBit) - _y) * (static_cast<double> (decBit) - _y);
    denominator = sqrt(denominatorLeft * denominatorRight);

    double r = numerator / denominator;
    std::cout << "\nCorrcoef: " << r << std::endl;
}