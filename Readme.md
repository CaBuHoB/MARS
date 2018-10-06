# MARS

MARS is a shared-key block cipher, with a block size of 128 bits and a variable key size, ranging from 128 to over 400 bits. It was designed to meet and exceed the requirements for a standard for shared-key encryption in the next few decades. The main theme behind the design of MARS is to get the best security/performance tradeoff by utilizing the strongest tools and techniques available today for designing block ciphers. As a result, MARS provides a very high level of security, combined with much better performance than other existing ciphers.

## Quick Start

    int main() {
        std::string message =   "MARS - a candidate cipher for AES. "
                                "MARS is a shared-key block cipher, with a block size of 128 bits and "
                                "a variable key size, ranging from 128 to over 400 bits.";
        ...
    }

Variable "message" assign the message you want to encode. As a result of the program, you will receive a randomly generated key, ciphertext with the distribution of "0" and "1", a decoded message and correlation coefficient for the input and output flow of the algorithm:

    Original: MARS - a candidate cipher for AES. MARS is a shared-key block cipher, with a block size of 128 bits and a variable key size, ranging from 128 to over 400 bits.
    Key: 1287413327 504862387 152522607 782537283 907780779 1590089769 1842987796 1456145547 454841597 1199799222 1149427744 1606081808 865661574 87959568

    Ciphertext: ?X��M�t��9�t)���K^�P�fC6)�������o �.zm0s�oOcS�}�*��W��e�Ť&X�999zhpW�!�ωINY����ʻi�%l��R��,H���7�.�z m.z?{�U�@�����.<E�a�&�X��*�qA%�Wp��O�sA
    Number of zeros: 633 49.4531%
    Number of units: 647 50.5469%

    Plaintext: MARS - a candidate cipher for AES. MARS is a shared-key block cipher, with a block size of 128 bits and a variable key size, ranging from 128 to over 400 bits.
    Corrcoef: 0.0129283

If you want to enter your key, replace the line in main:

    int main() {
        ...
        auto key = mars.getRandomKey();
        ...
    }

The key must be between 4 and 14 32-bit words, for example:

    int main() {
        ...
        std::vector<DWORD> key = {1, 2, 3, 4};
        ...
    }

## References
- [MARS - a candidate cipher for AES](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.35.5604&rep=rep1&type=pdf).
  Carolynn Burwick, Don Coppersmith, Edward D’Avignon, Rosario Gennaro, Shai Halevi, Charanjit Jutla, Stephen M. Matyas Jr., Luke O’Connor, Mohammad Peyravian, David Safford, Nevenko Zunic. IBM Corporation. Revised, September, 22 1999

