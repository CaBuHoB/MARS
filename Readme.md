# MARS

MARS is a shared-key block cipher, with a block size of 128 bits and a variable key size, ranging from 128 to over 400 bits. It was designed to meet and exceed the requirements for a standard for shared-key encryption in the next few decades. The main theme behind the design of MARS is to get the best security/performance tradeoff by utilizing the strongest tools and techniques available today for designing block ciphers. As a result, MARS provides a very high level of security, combined with much better performance than other existing ciphers.

## Quick Start

    int main() {
        std::string message = "Hello, world!";
        ...
    }

Variable "message" assign the message you want to encode. As a result of the program, you will receive a randomly generated key, chiphertext and a decoded message:

    Original: Hello, world!
    Key: 368540616 721753574 1088423854 1183147167 2065103748 1257566055 2121805365 1947632849
    Ciphertext: ���_�2_GQW=����(
    Plaintext: Hello, world!

## References
- [MARS - a candidate cipher for AES](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.35.5604&rep=rep1&type=pdf).
  Carolynn Burwick, Don Coppersmith, Edward D’Avignon, Rosario Gennaro, Shai Halevi, Charanjit Jutla, Stephen M. Matyas Jr., Luke O’Connor, Mohammad Peyravian, David Safford, Nevenko Zunic. IBM Corporation. Revised, September, 22 1999

