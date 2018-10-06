#include <iostream>
#include <vector>
#include <iterator>
#include "MARS/Mars.h"

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

int main() {
    std::string message = "Hello, world!";
    auto arr = stringToDWORDmas(message);
    std::cout << "Original: " << message << "\n";

    MARS mars;

    auto key = mars.getRandomKey();
    std::copy(key.begin(), key.end(), std::ostream_iterator<int>(std::cout << "Key: ", " "));
    std::cout << std::endl;

    std::vector<DWORD> encrypt;
    for (int i = 0; i < arr.size(); i += 4) {
        auto chiphertext = mars.encrypt({arr[i], arr[i + 1], arr[i + 2], arr[i + 3]}, key);
        encrypt.insert(encrypt.end(), chiphertext.begin(), chiphertext.end());
    }

    std::vector<DWORD> decrypt;
    for (int i = 0; i < encrypt.size(); i += 4) {
        auto plaintext = mars.decrypt({encrypt[i], encrypt[i + 1], encrypt[i + 2], encrypt[i + 3]}, key);
        decrypt.insert(decrypt.end(), plaintext.begin(), plaintext.end());
    }

    std::cout << "Ciphertext: " << masDWORDtoString(encrypt) << "\n";
    std::cout << "Plaintext: " << masDWORDtoString(decrypt) << "\n";

    return 0;
}