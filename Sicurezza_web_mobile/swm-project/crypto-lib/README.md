# Crypto-lib

The library provides an implementation of the PBKDF2 key-derivation function described the [RFC-2898](https://tools.ietf.org/html/rfc2898).

The function takes the `password` as an input and proceeds to calculate the derivation function by using 5 declared parameters:
* PseudoRandom Function: an efficiently computable function that emulates a _random oracle_, in this case is used HMAC-SHA1;
* Password: the `password` itself;
* Salt: randomly generated at every function call, with a length of 64 bits as per general recommendation;
* Number of iterations: in this case 65536 (which produces far more entropy than common web Password-Managers use, eg. LastPass makes 5000 iterations);
* Key length: in this case 128.

The output of the function is the `salt` and the `hashed password`.