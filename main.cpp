#include <iostream>
#include <vector>
#include <filesystem>

#include "MARS/Mars.h"
#include "workWithFilesAndCiphertext.h"

int main() {
    std::string filePath = "Files/image.bmp";
    unsigned long indexOfDot = filePath.rfind('.');
    indexOfDot = indexOfDot < filePath.length() ? indexOfDot : filePath.length();

    MARS mars;
    auto arr = fileToDWORDmas(filePath);

    auto key = mars.getRandomKey();
    std::copy(key.begin(), key.end(), std::ostream_iterator<unsigned>(std::cout << "Key: ", " "));
    std::cout << std::endl;

    std::vector<unsigned> encrypt;
    for (int i = 0; i < arr.size(); i += 4) {
        auto ciphertext = mars.encrypt({arr[i], arr[i + 1], arr[i + 2], arr[i + 3]}, key);
        encrypt.insert(encrypt.end(), ciphertext.begin(), ciphertext.end());
    }

    filePath.insert(indexOfDot, "_encrypt");
    masDWORDtoFile(filePath, encrypt, true);
    auto encryptFile = fileToDWORDmas(filePath);

    std::vector<unsigned> decrypt;
    for (int i = 0; i < encrypt.size(); i += 4) {
        auto plaintext = mars.decrypt({encryptFile[i], encryptFile[i + 1], encryptFile[i + 2], encryptFile[i + 3]}, key);
        decrypt.insert(decrypt.end(), plaintext.begin(), plaintext.end());
    }

    indexOfDot = filePath.rfind('.');
    indexOfDot = indexOfDot < filePath.length() ? indexOfDot : filePath.length();
    filePath.insert(indexOfDot, "_decrypt");
    masDWORDtoFile(filePath, decrypt);

    std::cout << "\nCiphertext\n";
    distribution(encrypt);
    corrCoef(encrypt, decrypt);

    return 0;
}
