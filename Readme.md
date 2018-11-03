# MARS

MARS is a shared-key block cipher, with a block size of 128 bits and a variable key size, ranging from 128 to over 400 bits. It was designed to meet and exceed the requirements for a standard for shared-key encryption in the next few decades. The main theme behind the design of MARS is to get the best security/performance tradeoff by utilizing the strongest tools and techniques available today for designing block ciphers. As a result, MARS provides a very high level of security, combined with much better performance than other existing ciphers.

## Quick Start

```C++
int main() {
    std::string filePath = "Files/image.bmp";
    ...
}
```

The variable “filePath” stores the path to the file you want to encode. As a result of the program, you will receive a randomly generated key, a encrypted file and its distribution “0” and “1”, a decoded file and [correlation coefficient](https://www.socscistatistics.com/tests/pearson/) for input and output flow algorithm:

    Key: 3260612125 272058955 999978797 1531222562 3216983359 4229743952 1255236363 1409535726 3705650868 2625221404 69201554 2588950460 2859282161 3395239520

    Ciphertext
    Number of zeros: 3146661 50.0047%
    Number of units: 3146075 49.9953%

    Corrcoef: 9.55003e-06

    "Files/image.bmp" - original file.
    "Files/image_encrypt.bmp" - encrypted file.
    "Files/image_encrypt_decrypt.bmp" - decrypted file.


If you want to enter your key, replace the line in main:

```C++
int main() {
    ...
    auto key = mars.getRandomKey();
    ...
}
```

The key must be between 4 and 14 32-bit words, for example:

```C++
int main() {
    ...
    std::vector<unsigned> key = {1, 2, 3, 4};
    ...
}
```

## References
- [MARS - a candidate cipher for AES](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.35.5604&rep=rep1&type=pdf).
  Carolynn Burwick, Don Coppersmith, Edward D’Avignon, Rosario Gennaro, Shai Halevi, Charanjit Jutla, Stephen M. Matyas Jr., Luke O’Connor, Mohammad Peyravian, David Safford, Nevenko Zunic. IBM Corporation. Revised, September, 22 1999

