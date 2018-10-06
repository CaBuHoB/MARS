#include <iostream>
#include <vector>

#include "MARS/Mars.h"
#include "workWithMessages.h"

int main() {
    std::string message = "MARS - a candidate cipher for AES. "
                          "MARS is a shared-key block cipher, with a block size of 128 bits and "
                          "a variable key size, ranging from 128 to over 400 bits.";
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

    std::cout << "\nCiphertext: " << masDWORDtoString(encrypt) << "\n";
    distribution(encrypt);
    std::cout << "\nPlaintext: " << masDWORDtoString(decrypt);

    corrCoef(encrypt, decrypt);

    return 0;
}
