#pragma once
//#include <mpirxx.h>
#include "Util.h"
//#include "util.h"

mpz_t* gen_primes();
//生成密钥对
key_pair* gen_key_pair();
//加密函数
char* encrypt(const char* plain_text, const char* key_n, const char* key_e);
//解密函数
char* decrypt(const char* cipher_text, const char* key_n, const char* key_d);
