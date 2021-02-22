# encrypt
Cryptography Library written in C++

## RSA
Generates 2048 bit RSA keypairs using `generateRSAKeyPair()` from keyGenerator.h
Encrypts and decrypts messages with RSA protocol.
There is also support for digital signatures.

### Encryption:
`
RSAKeyPair::Public key;
// Populate key from RSA key pair generated by recipient
uint2048 message;
// Populate message with some data...
uint2048 cipher = encrypt(message, key);
`

### Decryption:
`
RSAKeyPair kp = generateRSAKeyPair();
uint2048 cipher;
// Receive cipher from sender
uint2048 message = decrypt(cipher, kp.privateKey);
`

## AES-128
Generates 128-bit AES symmetric keys with `generateAESKey()` from keyGenerator.h
Encrypts and decrypts with AES-128 protocol

### Encryption:
`
AESKey key;
uint8 *message;
uint64 messageSize;
// Populate message buffer and size
// Create initialisation vector randomly
uint64 initVector = randomNumber();

uint8 *cipher = encrypt(message, messageSize, initVector, key);
`

### Decryption:
`
AESKey key;
uint8 *cipher;
uint64 messageSize;
uint64 initVector;
// Populate cipher buffer and size, and retrieve init vector

uint8 *message = decrypt(cipher, messageSize, initVector, key);
`

## SHA-256
Implements SHA-256 cryptographic hashing function with `sha256()` from sha.h

### Hashing
`
uint8 *message;
uint64 messageSize;
// Populate message and size
uint256 hash = sha256(message, messageSize);
`
