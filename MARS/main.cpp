#include <iostream>
#include <vector>
#include <iterator>
#include "MARS.h"

DWORD *stringToDWORDmas(const std::string &str) {
    return nullptr;
}

std::string masDWORDtoString(const std::array<DWORD, 4> &arr) {
    return " ";
}

int main() {
    MARS mars;


    std::vector<DWORD> D = {11111, 22222, 33333, 44444};
    auto key = mars.getRandomKey();
    key = {1, 2, 3, 4};

    copy(key.begin(), key.end(), std::ostream_iterator<int>(std::cout << "Key: ", " "));
    std::cout << std::endl;

    std::cout << "Original: " << D[0] << " " << D[1] << " " << D[2] << " " << D[3] << "\n";

    auto res = mars.getCiphertext(D, key);
    std::cout << "Ciphertext: " << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << "\n";

    std::vector<DWORD> ciphertext{0, 0, 0, 0};
    std::copy(res.begin(), res.end(), ciphertext.begin());
    res = mars.getPlaintext(ciphertext, key);
    std::cout << "Plaintext: " << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << "\n";

    return 0;
}