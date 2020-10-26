#pragma once
#include <string>
#include <bitset>
#include <mpir.h>

using namespace std;
//using std::string;
//using std::ifstream;
//using std::ofstream;

typedef std::bitset<8> byteu;
typedef std::bitset<32> word;

constexpr auto RSA_KEY_NAME = "rsa.key";
constexpr auto DH_KEY_NAME = "dh.key"; //输入输出的数字进制;

constexpr auto BASE = 16; //输入输出的数字进制;

struct key_pair
{
	int n_length;
	char* n;
	int d_length;
	char* d;
	int e_length;
	char* e;
};

struct dh_key
{
	int p_length;
	char* p;
	int a_length;
	char* a;

	char* xa;
	char* ya;
};

class Util
{
public:
	static string base64_encode(char const*, unsigned int len);
	static string base64_decode(string const& encoded_string);
	static string base64_decode_to_hexstring(string const& encoded_string);
	static string hexstring_encode_to_base64(const string& hex, int length);

	static string int_to_hexstring(int x);
	static string string_to_hexstring(unsigned char* x, int length);
	static void hexstring_to_string(string hex, unsigned char* x);
	static int hexstring_to_int(string hex);
	static char int_to_char(int i);
	static int char_to_int(char c);

	static string byte_to_string(byteu mtx[]);
	static void string_to_byte(string string, byteu mtx[]);
	static string byte_to_hex_string(byteu mtx[]);
	static void hex_string_to_byte(string string, byteu mtx[]);

	static string padding16(string s);
	static string unpadding16(string s);

	static bool is_file_open(string path);
	/**
	* \brief 密钥文件生成/更新
	* \param key_storage_path 两个密钥文件储存的位置
	*/
	static void gen_rsa_key_file(string key_storage_path);
	static key_pair* get_rsa_key(string key_storage_path);
	static string binary_in_to_hexstring(ifstream* ifs);
	static string binary_in_to_hexstring(ifstream* ifs, int length);
	static void hex_string_binary_out(ofstream* of, string hex);
	static void file_read_test(string path, string path2);
	static mpz_t* dh_gen_prime();
	static mpz_t* dh_gen_bigint();
	static mpz_t* dh_gen_yk(const char* ya, const char* xa, const char* p);
	static void gen_dh_key_file(string key_storage_path);
	static dh_key* get_dh_key(string key_storage_path);
private:
};
