#include <string>

int positiveModulo(const int a, const int b){
    /*
    Calculates a % b such that if a < 0, the result is positive (0 < result < b-1)
    */
    return (a % b + b) % b;
}

std::string runCaesarCipher(const std::string& inputText, const size_t key, const bool encrypt){
    /*
    Encrypts/decrypts some text using a standard Caesar Cipher

    const std::string& inputText: string of text to be encrypted/decrypted
    const size_t key: integer in range [0, 25] - Caesar Cipher shift
    const bool encrypt: if true, inputText will be shifted by 'key' to the right, or to the left if false.

    return: string of encrypted/decrypted text
    */
    std::string cipherText{""};
    int modifier{1};
    
    // If we want to decrypt, this modifier turns key -> -key
    if (!encrypt){
        modifier = -1;
    }
    // ASCII representations of capital letters range from A: 65 to Z: 90
    // Add the key, subtract the ASCII offset, modulo 26 and re-add the offset
    // This accounts for e.g. Z->A if key=1
    for (char c : inputText){
        cipherText += (char)(positiveModulo(c + modifier * key - 65, 26) + 65);
    }
    return cipherText;
}