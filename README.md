# UUIDv3
A C implementation to generate UUID version 3 using MAC address and UNIX timestamp

## UUID version 3
* Generated by hashing namespace identifier and name.
* Same namespace and name will map to the same UUID.
* But the name or namespace cannot be derived from the UUID, even if one of them is specified, except by brute force search.

## C Code for generating UUIDv3
* This was done with the help of openssl and cryptographic functions in the `openssl/sha.h` library.
* MAC address was extracted from the sub-file system in Ubuntu.
    * Command: `$cat /sys/class/net/enp0s3/address` 
* UNIX timestamp was extracted using `time.h` library with the `time()` function.
* Hash used - SHA256
![SHA 256](https://en.bitcoinwiki.org/upload/en/images/f/f8/Sha-256.jpg)
