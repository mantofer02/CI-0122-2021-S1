#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <string.h>
#include "openssl/des.h"
#include <fstream>

using namespace std;

std::string des_encrypt(const std::string &clearText, const std::string &key)
{
    std::string cipherText;

    DES_cblock keyEncrypt;
    memset(keyEncrypt, 0, 8);

    if (key.length() <= 8)
        memcpy(keyEncrypt, key.c_str(), key.length());
    else
        memcpy(keyEncrypt, key.c_str(), 8);

    DES_key_schedule keySchedule;
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);

    const_DES_cblock inputText;
    DES_cblock outputText;
    std::vector<unsigned char> vecCiphertext;
    unsigned char tmp[8];

    for (int i = 0; i < clearText.length() / 8; i++)
    {
        memcpy(inputText, clearText.c_str() + i * 8, 8);
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCiphertext.push_back(tmp[j]);
    }

    if (clearText.length() % 8 != 0)
    {
        int tmp1 = clearText.length() / 8 * 8;
        int tmp2 = clearText.length() - tmp1;
        memset(inputText, 0, 8);
        memcpy(inputText, clearText.c_str() + tmp1, tmp2);
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCiphertext.push_back(tmp[j]);
    }

    cipherText.clear();
    cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());
    return cipherText;
}

std::string des_decrypt(const std::string &cipherText, const std::string &key)
{
    std::string clearText;

    DES_cblock keyEncrypt;
    memset(keyEncrypt, 0, 8);

    if (key.length() <= 8)
        memcpy(keyEncrypt, key.c_str(), key.length());
    else
        memcpy(keyEncrypt, key.c_str(), 8);

    DES_key_schedule keySchedule;
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);

    const_DES_cblock inputText;
    DES_cblock outputText;
    std::vector<unsigned char> vecCleartext;
    unsigned char tmp[8];

    for (int i = 0; i < cipherText.length() / 8; i++)
    {
        memcpy(inputText, cipherText.c_str() + i * 8, 8);
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCleartext.push_back(tmp[j]);
    }

    if (cipherText.length() % 8 != 0)
    {
        int tmp1 = cipherText.length() / 8 * 8;
        int tmp2 = cipherText.length() - tmp1;
        memset(inputText, 0, 8);
        memcpy(inputText, cipherText.c_str() + tmp1, tmp2);
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCleartext.push_back(tmp[j]);
    }

    clearText.clear();
    clearText.assign(vecCleartext.begin(), vecCleartext.end());

    return clearText;
}

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        cout << "Error, parameter format must be <program> <opcode> <string/file> <password>" << endl;
    }

    unsigned char ckey[] = "Gatto se la come";

    if ("ECS" == string(argv[1]))
    {
        string line, key;
        line = string(argv[2]);
        key = string(argv[3]);
        string encrypted = des_encrypt(line, key);
        cout << encrypted << endl;
    }

    else if ("DCS" == string(argv[1]))
    {
        string line, key;
        line = string(argv[2]);
        key = string(argv[3]);
        string decrypted = des_decrypt(line, key);
        cout << decrypted << endl;
    }

    else if ("ECF" == string(argv[1]))
    {
        string content = "";
        string key = string(argv[3]);

        string path = string(argv[2]);

        ifstream input(path);
        ofstream output("encoded-" + path);

        char c;
       while (input >> c){
           content += c;
       }

       string encrypted = des_encrypt(content, key);
       output << encrypted;
    }

    else if ("DCF" == string(argv[1]))
    {
        string content = "";
        string key = string(argv[3]);

        string path = string(argv[2]);

        ifstream input(path);
        ofstream output("decoded-" + path);

        char c;
       while (input >> c){
           content += c;
       }

       string encrypted = des_decrypt(content, key);
       output << encrypted;
    }

    return 0;
}