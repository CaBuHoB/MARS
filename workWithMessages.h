#include <iterator>
#include <bitset>
#include <vector>
#include <lcms.h>
#include <iostream>
#include <fstream>

std::vector<unsigned> fileToDWORDmas(const std::string &filePath) {
    std::ifstream fs(filePath, std::ios_base::out | std::ios_base::binary);
    if (fs.fail()) {
        exit(1);
    }

    std::vector<unsigned> arr;
    fs.seekg(0, std::ios::end);
    auto fileSize = fs.tellg();
    fs.seekg(0, std::ios::beg);

    auto sizeOfBuffer = fileSize / sizeof(unsigned);

    arr.resize(static_cast<unsigned long>(sizeOfBuffer + 1));
    fs.read(reinterpret_cast<char *>(arr.data()), fileSize);

    if (arr.size() % 4 != 0)
        arr.resize(arr.size() + arr.size() % 4);
    return arr;
}

void masDWORDtoFile(const std::string &filePath, const std::vector<DWORD> &arr) {
    std::ofstream fs(filePath, std::ios_base::out | std::ios_base::binary);
    if (fs.fail()) {
        exit(1);
    }

    std::vector<unsigned> arrCopy(arr.size());
    std::copy(arr.begin(), arr.end(), arrCopy.begin());
    while (arrCopy.back() == 0)
        arrCopy.pop_back();
    fs.write(reinterpret_cast<const char *>(arrCopy.data()), arrCopy.size() * 4);
}

std::vector<unsigned> stringToDWORDmas(const std::string &str) {
    std::vector<unsigned> arr;
    unsigned num = 0;
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

std::string masDWORDtoString(const std::vector<unsigned> &arr) {
    std::string str;
    for (const auto num : arr) {
        for (int i = 0; i < 4; ++i) {
            BYTE symb = static_cast<BYTE>(num >> (i * 8));
            str += char(symb);
        }
    }

    return str;
}

std::string getBits(const std::vector<DWORD> &arr) {
    std::string arrBits;
    for (const auto dword : arr) {
        std::bitset<32> bits(dword);
        arrBits += bits.to_string();
    }

    return arrBits;
}

void distribution(const std::vector<DWORD> &encrypt) {
    std::string encBits = getBits(encrypt);

    unsigned col = 0;
    for (auto bit : encBits) {
        if (bit == '0')
            col++;
    }
    std::cout << "Number of zeros: " << col << " " << col * 1.0 / encBits.length() * 100 << "%\n";
    std::cout << "Number of units: " << encBits.length() - col << " ";
    std::cout << (encBits.length() - col) * 1.0 / encBits.length() * 100 << "%\n";
}

void corrCoef(const std::vector<DWORD> &encrypt, const std::vector<DWORD> &decrypt) {
    std::string encBits = getBits(encrypt);
    std::string decBits = getBits(decrypt);

    double _x = 0;
    for (const auto bit : encBits)
        _x += static_cast<unsigned> (bit);
    _x /= encBits.length();

    double _y = 0;
    for (const auto bit : decBits)
        _y += static_cast<unsigned> (bit);
    _y /= decBits.length();

    double numerator = 0;
    for (int i = 0; i < encBits.length(); ++i)
        numerator += (static_cast<unsigned> (encBits[i]) - _x) * (static_cast<unsigned> (decBits[i]) - _y);

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
