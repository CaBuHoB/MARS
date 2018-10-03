#include <iostream>
#include <vector>
#include "MARS.h"

int main() {
    std::vector<DWORD> D = {1819043144,1830825071,1634607225,2123117};
    std::vector<DWORD> key = {1,2,3,4};
    MARS mars;
    auto res = mars.getCiphertext(D, key);
    std::cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << "\n";
    res = mars.getEncrypted(D, key);
    std::cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << "\n";

    return 0;
}