#include <iostream>
#include <vector>
#include <filesystem>

#include "MARS/Mars.h"
#include "workWithMessages.h"

int main() {
    std::string filePath = "/home/maxim/Documents/Projects/C++/Cryptography/Lab 2/Files/MessageReplay.py";
    unsigned long indexOfDot = filePath.rfind('.');
    indexOfDot = indexOfDot < filePath.length() ? indexOfDot : filePath.length();

    MARS mars;
    auto arr = fileToDWORDmas(filePath);

    auto key = mars.getRandomKey();
    std::copy(key.begin(), key.end(), std::ostream_iterator<DWORD>(std::cout << "Key: ", " "));
    std::cout << std::endl;
    std::cout << arr[0] << std::endl;

    std::vector<DWORD> encrypt;
    for (int i = 0; i < arr.size(); i += 4) {
        auto chiphertext = mars.encrypt({arr[i], arr[i + 1], arr[i + 2], arr[i + 3]}, key);
        encrypt.insert(encrypt.end(), chiphertext.begin(), chiphertext.end());
    }
    std::cout << encrypt[0] << std::endl;

    filePath.insert(indexOfDot, "_encrypt");
    masDWORDtoFile(filePath, encrypt);

    std::vector<DWORD> decrypt;
    for (int i = 0; i < encrypt.size(); i += 4) {
        auto plaintext = mars.decrypt({encrypt[i], encrypt[i + 1], encrypt[i + 2], encrypt[i + 3]}, key);
        decrypt.insert(decrypt.end(), plaintext.begin(), plaintext.end());
    }
    std::cout << decrypt[0] << std::endl;

    indexOfDot = filePath.rfind('.');
    indexOfDot = indexOfDot < filePath.length() ? indexOfDot : filePath.length();
    filePath.insert(indexOfDot, "_decrypt");
    masDWORDtoFile(filePath, decrypt);

    std::cout << "\nCiphertext\n";
    distribution(encrypt);
    corrCoef(encrypt, decrypt);

    return 0;
}
