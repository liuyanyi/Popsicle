#include "controller.h"
#include "MD5.h"
#include "Util.h"
#include "aes.h"
#include "rsa.h"
#include <ctime>
#include <iostream>

using std::cout;
using std::endl;

string controller::aes_encrypt(const string &plain_text, const string &key, const int mode) {
    Aes_block_Operator a;
    byteu              k[16];

    //有修改
    //Util::string_to_byte(key, k);
    Util::hex_string_to_byte(key, k);

    byteu ivb[16];
    Util::string_to_byte("1111111111111111", ivb);

    string result;

    string padd  = Util::padding16(plain_text);
    int    round = padd.size() / 16;
    for (int i = 0; i < round; i++) {
        string sub = padd.substr(i * 16, 16);
        byteu  info[16];

        Util::string_to_byte(sub, info);

        if (mode == AES_CBC) {
            for (int j = 0; j < 16; j++) {
                info[j] ^= ivb[j];
            }
        }

        a.encrypt(info, k);

        string encstring = Util::byte_to_hex_string(info);
        result += encstring;

        if (mode == AES_CBC) {
            for (int j = 0; j < 16; j++) {
                ivb[j] = info[j];
            }
        }
    }

    return result;
}

void controller::aes_encrypt(unsigned char *text, const string &key, int length) {
    Aes_block_Operator a;
    byteu              k[16];
    Util::hex_string_to_byte(key, k);

    byteu ivb[16];
    Util::string_to_byte("1111111111111111", ivb);

    //string padd = Util::padding16(plain_text);
    int round = length / 16;
    for (int i = 0; i < round; i++) {
        //cout << i << endl;
        //string sub = padd.substr(i * 16, 16);
        byteu info[16];
        for (int j = 0; j < 16; j++)
            info[j] = byteu(text[16 * i + j]);
        //Util::string_to_byte(sub, info);

        /*if (mode == AES_CBC) {
			for (int j = 0; j < 16; j++) {
				info[j] ^= ivb[j];
			}
		}*/

        a.encrypt(info, k);
        for (int j = 0; j < 16; j++)
            text[16 * i + j] = info[j].to_ulong();

        //string encstring = Util::byte_to_hex_string(info);
        //result += encstring;

        /*if (mode == AES_CBC) {
			for (int j = 0; j < 16; j++) {
				ivb[j] = info[j];
			}
		}*/
    }

    //return result;
}

string controller::aes_decrypt(const string &cipher_text, const string &key, const int mode) {
    Aes_block_Operator a;
    byteu              k[16];
    //修改
    //Util::string_to_byte(key, k);
    Util::hex_string_to_byte(key, k);

    byteu ivb[16];
    Util::string_to_byte("1111111111111111", ivb);

    int    round = cipher_text.size() / 32;
    string result;

    for (int i = 0; i < round; i++) {
        string sub = cipher_text.substr(i * 32, 32);
        byteu  info[16];
        Util::hex_string_to_byte(sub, info);

        a.decrypt(info, k);

        if (mode == AES_CBC) {
            for (int j = 0; j < 16; j++) {
                info[j] ^= ivb[j];
            }
            Util::hex_string_to_byte(sub, ivb);
        }

        string decstring = Util::byte_to_string(info);
        result += decstring;
    }
    return Util::unpadding16(result);
}

void controller::aes_decrypt(unsigned char *text, const string &key, int length) {
    Aes_block_Operator a;
    byteu              k[16];
    Util::hex_string_to_byte(key, k);

    //byte ivb[16];
    //Util::string_to_byte("1111111111111111", ivb);

    int    round = length / 16;
    string result;

    for (int i = 0; i < round; i++) {
        //string sub = cipher_text.substr(i * 32, 32);
        byteu info[16];
        //Util::hex_string_to_byte(sub, info);
        for (int j = 0; j < 16; j++)
            info[j] = byteu(text[16 * i + j]);

        a.decrypt(info, k);
        for (int j = 0; j < 16; j++)
            text[16 * i + j] = info[j].to_ulong();
        /*if (mode == AES_CBC)
		{
			for (int j = 0; j < 16; j++) {
				info[j] ^= ivb[j];
			}
			Util::hex_string_to_byte(sub, ivb);
		}*/

        //string decstring = Util::byte_to_string(info);
        //result += decstring;
    }
    //return Util::unpadding16(result);
}

string controller::rsa_encrypt(string plain_text, string key_file_path, int mode) {
    key_pair *p = Util::get_rsa_key(key_file_path);
    //    cout << endl << endl;
    //    cout << "n = " << p->n << endl;
    //    cout << "d = " << p->d << endl;
    //    cout << "e = " << p->e << endl;
    char *c_text;
    switch (mode) {
    case ENCRYPT:
        c_text = encrypt(plain_text.c_str(), p->n, p->e);
        break;
    case SIGN:
        c_text = encrypt(plain_text.c_str(), p->n, p->d);
        break;
    }
    //cout << "密文为：" << c_text << endl;

    return c_text;
}

string controller::rsa_decrypt(string cipher_text, string key_file_path, int mode) {
    key_pair *p = Util::get_rsa_key(key_file_path);
    char *    plain_text;
    switch (mode) {
    case ENCRYPT:
        plain_text = decrypt(cipher_text.c_str(), p->n, p->d);
        break;
    case SIGN:
        plain_text = decrypt(cipher_text.c_str(), p->n, p->e);
        break;
    }
    //cout << "明文为：" << plain_text << endl;
    //string org = plain_text;
    //cout << "\n明文为：\n" << org.c_str() << endl;
    return plain_text;
}

string controller::rsa_sign_decrypt(string cipher_text, string key_file_path,string n) {
    key_pair *p = Util::get_rsa_key(key_file_path);
    char *plain_text;
    plain_text = decrypt(cipher_text.c_str(), n.c_str(), p->e);
    return string(plain_text);
}

dh_key *controller::dh_generator(string pa_file_path) {
    dh_key *d = Util::get_dh_key(std::move(pa_file_path));
    if (d == nullptr)
        return nullptr;

    mpz_t *xa  = Util::dh_gen_bigint();
    char * xac = new char[150];
    mpz_get_str(xac, 16, *xa);
    mpz_clear(*xa);

    d->xa = xac;

    mpz_t *ya = Util::dh_gen_yk(d->a, d->xa, d->p);

    char *yac = new char[1000];
    mpz_get_str(yac, 16, *ya);

    d->ya = yac;

    return d;
}

string controller::dh_operator(dh_key *d, string ybc) {
    mpz_t *ka  = Util::dh_gen_yk(ybc.c_str(), d->xa, d->p);
    char * kac = new char[1000];
    mpz_get_str(kac, 16, *ka);
    //cout << "Ka " << kac << endl;
    
    return controller::md5_generator(kac);
}

string controller::md5_generator(const string text) {
    return MD5(text).toStr();
}

bool controller::file_handle(string input_file_path, string output_file_path,string key, int mode) {
    FILE *file1;
    FILE *file2;

    fopen_s(&file1, input_file_path.c_str(), "rb");
    fopen_s(&file2, output_file_path.c_str(), "wb");

    const auto start     = clock();
    int        remainder = 0;
    if (file1 != nullptr && file2 != nullptr) {
        while (!feof(file1)) {
            const int      length      = 16 * 1024 * 1024;
            unsigned char *c           = new unsigned char[length + 16];
            int            real_length = fread(c, 1, length, file1);

            int temp_length = real_length;

            if (feof(file1)) {
                remainder   = real_length % 16;
                temp_length = temp_length - real_length % 16;
                if (mode == FILE_DECRYPT)
                    temp_length -= 16;
            }

            if (mode == FILE_ENCRYPT)
                aes_encrypt(c, key, temp_length);
            else
                aes_decrypt(c, key, temp_length);

            fwrite(c, 1, temp_length, file2);
            delete[] c;
        }

        if (mode == FILE_ENCRYPT) {
            int           tttt = fseek(file1, -remainder, SEEK_END);
            unsigned char cend[16];
            if (!feof(file1))
                fread(cend, 1, remainder, file1);
            for (int i = remainder; i < 16; i++)
                cend[i] = 16 - remainder;
            aes_encrypt(cend, key, 16);
            fwrite(cend, 1, 16, file2);
        } else {
            fseek(file1, -16, SEEK_END);
            unsigned char cend[16];
            fread(cend, 1, 16, file1);
            aes_decrypt(cend, key, 16);
            int del = cend[15];
            fwrite(cend, 1, 16 - del, file2);
        }

        fclose(file1);
        fclose(file2);

        const auto end = clock();
        auto       dur = static_cast<double>(end - start);
        cout << "时间" << dur / CLOCKS_PER_SEC << "s" << endl;

        return true;
    }

    return false;
}