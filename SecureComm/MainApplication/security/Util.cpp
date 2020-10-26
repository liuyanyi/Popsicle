#include "Util.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <QDebug>

#include "controller.h"
#include "rsa.h"

//using namespace std;
using std::vector;
using std::fstream;
using std::ios;
using std::stringstream;
using std::cout;
using std::endl;
using std::setw;
using std::setfill;
using std::hex;

static const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static inline bool is_base64(unsigned char c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}

// Base64部分
string Util::base64_encode(char const* bytes_to_encode, unsigned int in_len)
{
	string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';
	}

	return ret;
}

string Util::base64_decode(string const& encoded_string)
{
	size_t in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_];
		in_++;
		if (i == 4)
		{
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]) & 0xff;

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i)
	{
		for (j = 0; j < i; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]) & 0xff;

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

string Util::hexstring_encode_to_base64(const string& hex, int length)
{
	std::vector<char> array;
	array.reserve(length / 2 + 1);
	//char* array = new char[length];

	for (int i = 0; i < length / 2; i++)
	{
		int sss = char_to_int(hex[2 * i]) * 16 + char_to_int(hex[2 * i + 1]);
		//cout << endl << sss << endl;
		array.push_back(sss);
	}
	for (int i = 0; i < length / 2; i++)
	{
		//cout << endl << endl << int(array[i]) << endl << endl;
	}
	string en = base64_encode(&array[0], hex.size() / 2);

	return en;
}

string Util::base64_decode_to_hexstring(string const& encoded_string)
{
	size_t in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	string ret;
	//std::vector<char> arr;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_];
		in_++;
		if (i == 4)
		{
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]) & 0xff;

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += int_to_hexstring(char_array_3[i]);
			i = 0;
		}
	}

	if (i)
	{
		for (j = 0; j < i; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]) & 0xff;

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

		for (j = 0; (j < i - 1); j++)
			ret += int_to_hexstring(char_array_3[j]);
	}

	return ret;
}

// 十六进制字符处理
string Util::int_to_hexstring(const int x)
{
	char c[3];
	c[0] = int_to_char(x / 16);
	c[1] = int_to_char(x % 16);
	c[2] = '\0';
	return c;
}

string Util::string_to_hexstring(unsigned char* x, int length)
{
	string temp;
	//cout << length << endl;
	for (int i = 0; i < length; i++)
	{
		//cout << (int)x[i] << endl;
		temp += int_to_hexstring(x[i]);
	}

	return temp;
}

void Util::hexstring_to_string(string hex, unsigned char* x)
{
	int length = hex.size() / 2;
	for (int i = 0; i < length; i++)
	{
		x[i] = hexstring_to_int(hex.substr(i * 2, 2));
	}
}

int Util::hexstring_to_int(string hex)
{
	//仅限两位转int
	return char_to_int(hex[1]) + char_to_int(hex[0]) * 16;
}

char Util::int_to_char(const int i)
{
	int c;
	if (i >= 10)
	{
		c = i + 87;
	}
	else
	{
		c = i + 48;
	}
	return static_cast<char>(c);
}

int Util::char_to_int(const char c)
{
	int i;
	if (c >= 'A')
	{
		i = c - 87;
	}
	else
	{
		i = c - 48;
	}
	return i;
}

// Byte处理
// key2String16
string Util::byte_to_string(byteu mtx[])
{
	string s = "";
	char ss[17];
	int length = 16;
	for (int i = 0; i < length; i++)
	{
		ss[i] = mtx[i][7] * 128 + mtx[i][6] * 64 + mtx[i][5] * 32 + mtx[i][4] * 16
			+ mtx[i][3] * 8 + mtx[i][2] * 4 + mtx[i][1] * 2 + mtx[i][0] * 1;
	}
	ss[16] = '\0';
	return ss;
}

//string2key
void Util::string_to_byte(string string, byteu mtx[])
{
	//必须传长为16的string
	for (int i = 0; i < 16; i++)
		mtx[i] = 0;
	if (string.length() != 16)
		return;
	for (int i = 0; i < 16; i++)
		mtx[i] = byteu(string[i]);
}

//byte2String16
string Util::byte_to_hex_string(byteu mtx[])
{
	string s = "";
	char ss[33];
	int length = 16;
	for (int i = 0; i < length; i++)
	{
		int temp1 = mtx[i][7] * 8 + mtx[i][6] * 4 + mtx[i][5] * 2 + mtx[i][4] * 1;
		int temp2 = mtx[i][3] * 8 + mtx[i][2] * 4 + mtx[i][1] * 2 + mtx[i][0] * 1;
		ss[2 * i] = int_to_char(temp1);
		ss[2 * i + 1] = int_to_char(temp2);
	}

	ss[32] = '\0';
	return ss;
}

//string2byte16
void Util::hex_string_to_byte(string string, byteu mtx[])
{
	for (int i = 0; i < 16; i++)
	{
		int temp1 = char_to_int(string[2 * i]) * 16 + char_to_int(string[2 * i + 1]);
		mtx[i] = byteu(temp1);
	}
}

// AES填充
string Util::padding16(string s)
{
	//扩成16
	int pad;
	if (s == "")
	{
		string ss = "";
		for (int i = 0; i < 16; i++)
		{
			ss += 16;
		}

		return ss;
	}
	if (s.size() <= 16)
	{
		pad = 16 - s.size();
	}
	else
	{
		pad = 16 - s.size() % 16;
	}

	if (pad == 0)
	{
		for (int i = 0; i < 16; i++)
		{
			s += 16;
		}
		return s;
	}

	char c = pad;
	for (int i = 0; i < pad; i++)
		s += c;
	return s;
}

string Util::unpadding16(string s)
{
	//解扩
	char last = s[s.size() - 1];
	//cout << (int)last;
	if (last == 16 && s.size() == 16)
	{
		return "";
	}
	return s.substr(0, s.size() - last);
}

// 文件处理
bool Util::is_file_open(string path)
{
	fstream s;
	s.open(path, ios::in);
	bool b = s.is_open();
	s.close();
	return b;
}

void Util::gen_rsa_key_file(string key_storage_path)
{
	ofstream key;
	key.open(key_storage_path + RSA_KEY_NAME, ios::trunc | ios::binary);
	if (!key.is_open())
	{
		//cout << "ERROR" << endl;
		return;
	}
	key_pair* pair = gen_key_pair();
	stringstream ss;
	//key << "---------------RSA Key Start---------------\n";

	ss << "00000006525341";

	ss << setw(8) << setfill('0') << hex << pair->e_length;
	//cout << setw(8) << setfill('0') << hex << pair->e_length << endl;
	if (pair->e_length % 2 == 1)
		ss << '0';

	ss << pair->e;
	//cout << pair->e << endl;

	ss << setw(8) << setfill('0') << hex << pair->d_length;
	//cout << setw(8) << setfill('0') << hex << pair->d_length << endl;
	if (pair->d_length % 2 == 1)
		ss << '0';

	ss << pair->d;
	//cout << pair->d << endl;

	ss << setw(8) << setfill('0') << hex << pair->n_length;
	//cout << setw(8) << setfill('0') << hex << pair->n_length << endl;
	if (pair->n_length % 2 == 1)
		ss << '0';

	ss << pair->n;
	//cout << pair->n << endl;

	//string base64 = hexstring_encode_to_base64(ss.str(), ss.str().length());
	//string base64 = ss.str();
	//key << base64;
	hex_string_binary_out(&key, ss.str());
	//key << "\n----------------RSA Key End----------------\n";
}

key_pair* Util::get_rsa_key(string key_storage_path)
{
	ifstream key;
	key.open(key_storage_path + RSA_KEY_NAME, ios::binary);
	if (!key)
		return nullptr;
	string res = binary_in_to_hexstring(&key);
	long length = res.size();
	string siz = res.substr(0, 8);
	unsigned long l = char_to_int(siz[0]) * 0x10000000 + char_to_int(siz[1]) * 0x1000000 + char_to_int(siz[2]) *
		0x100000 + char_to_int(siz[3]) * 0x10000
		+ char_to_int(siz[4]) * 0x1000 + char_to_int(siz[5]) * 0x100 + char_to_int(siz[6]) * 0x10 + char_to_int(siz[7])
		* 0x1;
	string veri = res.substr(8, l);
	if (veri != "525341")
		return nullptr;
	vector<string> v;
	for (int i = 0, tt = 8 + l; i < 3; i++)
	{
		siz = res.substr(tt, 8);

		l = char_to_int(siz[0]) * 0x10000000 + char_to_int(siz[1]) * 0x1000000 + char_to_int(siz[2]) * 0x100000 +
			char_to_int(siz[3]) * 0x10000
			+ char_to_int(siz[4]) * 0x1000 + char_to_int(siz[5]) * 0x100 + char_to_int(siz[6]) * 0x10 +
			char_to_int(siz[7]) * 0x1;
		v.push_back(std::to_string(l));
		if (l % 2 == 1)
			tt++;
		v.push_back(res.substr(tt + 8, l));
		tt += 8 + l;
	}
	key_pair* k = new key_pair;

	//int temp1;

	k->e_length = stoi(v[0]);
	/*if (k->e_length % 2 == 1)
		temp1 = k->e_length + 1;
	else
		temp1 = k->e_length;*/

	char* t1 = new char[stoi(v[0]) + 1];
	strcpy_s(t1, stoi(v[0]) + 1, v[1].c_str());
	k->e = t1;
	//cout << k->e << endl;

	k->d_length = stoi(v[2]);
	/*if (k->d_length % 2 == 1)
		temp1 = k->d_length + 1;
	else
		temp1 = k->d_length;*/

	char* t2 = new char[stoi(v[2]) + 1];
	strcpy_s(t2, stoi(v[2]) + 1, v[3].c_str());
	k->d = t2;
	//cout << k->d << endl;

	k->n_length = stoi(v[4]);
	/*if (k->n_length % 2 == 1)
		temp1 = k->n_length + 1;
	else
		temp1 = k->n_length;*/

	char* t3 = new char[stoi(v[4]) + 1];
	strcpy_s(t3, stoi(v[4]) + 1, v[5].c_str());
	k->n = t3;
	//cout << k->n << endl;

	return k;
}

string Util::binary_in_to_hexstring(ifstream* ifs)
{
	//string result;
	stringstream ss;
	while (ifs->peek() != EOF)
	{
		int c = 0;
		ifs->read(reinterpret_cast<char*>(&c), 1);

		ss << hex << setw(2) << setfill('0') << c;
	}
	return ss.str();
}

string Util::binary_in_to_hexstring(ifstream* ifs, int length)
{
	stringstream ss;
	for (int i = 0; i < length && ifs->peek() != EOF; i++)
	{
		int c = 0;
		ifs->read(reinterpret_cast<char*>(&c), 1);

		ss << hex << setw(2) << setfill('0') << c;
	}
	return ss.str();
}

void Util::hex_string_binary_out(ofstream* of, string hex)
{
	int length = hex.size() / 2;
	for (int i = 0; i < length; i++)
	{
		int temp = hexstring_to_int(hex.substr(2 * i, 2));
		of->write(reinterpret_cast<char*>(&temp), 1);
	}
	if (hex.size() % 2 == 1)
	{
		char temp[3];
		temp[0] = hex[hex.size() - 1];
		temp[1] = '0';
		temp[2] = '\0';
		int mtl = hexstring_to_int(temp);
		of->write(reinterpret_cast<char*>(&temp), 1);
	}
}

void Util::file_read_test(string path, string path2)
{
	FILE* file1;
	FILE* file2;

	fopen_s(&file1, path.c_str(), "rb");
	fopen_s(&file2, path2.c_str(), "wb");

	const auto start = clock();
	if (file1 != nullptr && file2 != nullptr)
	{
		while (!feof(file1))
		{
			const int length = 16 * 1024 * 1024;
			unsigned char* c = new unsigned char[length];
			int real_length = fread(c, 1, length, file1);

			controller::aes_decrypt(c, "1234123412341234", real_length);
			fwrite(c, 1, real_length, file2);
			delete[] c;
		}
		const auto end = clock();
		auto dur = static_cast<double>(end - start);
		//cout << "时间" << dur / CLOCKS_PER_SEC << "s" << endl;
		fclose(file1);
		fclose(file2);
	}
}

mpz_t* Util::dh_gen_prime()
{
	gmp_randstate_t grt;
	gmp_randinit_default(grt);
	gmp_randseed_ui(grt, time(nullptr));

	mpz_t key_p;
	mpz_init(key_p);

	mpz_urandomb(key_p, grt, 512); //随机生成一个大整数

	mpz_t* result = new mpz_t[1];
	//mpz_t result;
	mpz_init(result[0]);

	mpz_nextprime(result[0], key_p); //使用GMP自带的素数生成函数

	mpz_clear(key_p);

	//char* temp = new char[310];
	//mpz_get_str(temp,16,key_p);
	//cout<<temp<<endl;

	return result;
}

mpz_t* Util::dh_gen_bigint()
{
	gmp_randstate_t grt;
	gmp_randinit_default(grt);
	gmp_randseed_ui(grt, clock());

	//mpz_t key_p;
	mpz_t* key_p = new mpz_t[1];
	mpz_init(key_p[0]);

	mpz_urandomb(key_p[0], grt, 128); //随机生成一个大整数
	//Sleep(1000);
	return key_p;
}

mpz_t* Util::dh_gen_yk(const char* ya, const char* xa, const char* p)
{
	mpz_t yam, xam, pm;
	mpz_t* result = new mpz_t[1];
	mpz_init_set_str(yam, ya, BASE);
	mpz_init_set_str(xam, xa, BASE);
	mpz_init_set_str(pm, p, BASE);
	mpz_init_set_ui(result[0], 0);

	mpz_powm(result[0], yam, xam, pm); //使用GMP中模幂计算函数

	//char* result = new char[KEY_LENGTH + 10];
	//mpz_get_str(result, BASE, C);

	return result;
}

void Util::gen_dh_key_file(string key_storage_path)
{
	ofstream key;

	key.open(key_storage_path + DH_KEY_NAME, ios::trunc | ios::binary);
	if (!key.is_open())
	{
		//cout << "ERROR" << endl;
		return;
	}
	mpz_t* p = dh_gen_prime();
	mpz_t a;
	mpz_init_set_ui(a, 5);
	char* pc = new char[550];
	mpz_get_str(pc, 16, *p);
	mpz_clear(*p);
	char* ac = new char[10];
	mpz_get_str(ac, 16, a);
	mpz_clear(a);
	string temp = pc;
	int plength = temp.size();
	temp = ac;
	int alength = temp.size();

	stringstream ss;

	ss << "000000044448";

	ss << setw(8) << setfill('0') << hex << alength;
	if (alength % 2 == 1)
		ss << '0';

	ss << ac;

	ss << setw(8) << setfill('0') << hex << plength;
	if (plength % 2 == 1)
		ss << '0';

	ss << pc;
	//cout << pc << endl;

	//string base64 = hexstring_encode_to_base64(ss.str(), ss.str().length());
	//string base64 = ss.str();
	//key << base64;
	hex_string_binary_out(&key, ss.str());
	//key << "\n----------------RSA Key End----------------\n";
}

dh_key* Util::get_dh_key(string key_storage_path)
{
	ifstream key;
	key.open(key_storage_path + DH_KEY_NAME, ios::binary);
	if (!key)
		return nullptr;
	string res = binary_in_to_hexstring(&key);
	long length = res.size();
	string siz = res.substr(0, 8);
	unsigned long l = char_to_int(siz[0]) * 0x10000000 + char_to_int(siz[1]) * 0x1000000 + char_to_int(siz[2]) *
		0x100000 + char_to_int(siz[3]) * 0x10000
		+ char_to_int(siz[4]) * 0x1000 + char_to_int(siz[5]) * 0x100 + char_to_int(siz[6]) * 0x10 + char_to_int(siz[7])
		* 0x1;
	string veri = res.substr(8, l);
	if (veri != "4448")
		return nullptr;
	vector<string> v;
	for (int i = 0, tt = 8 + l; i < 2; i++)
	{
		siz = res.substr(tt, 8);

		l = char_to_int(siz[0]) * 0x10000000 + char_to_int(siz[1]) * 0x1000000 + char_to_int(siz[2]) * 0x100000 +
			char_to_int(siz[3]) * 0x10000
			+ char_to_int(siz[4]) * 0x1000 + char_to_int(siz[5]) * 0x100 + char_to_int(siz[6]) * 0x10 +
			char_to_int(siz[7]) * 0x1;
		v.push_back(std::to_string(l));
		if (l % 2 == 1)
			tt++;
		v.push_back(res.substr(tt + 8, l));
		tt += 8 + l;
	}
	dh_key* d = new dh_key;

	//int temp1;

	d->a_length = stoi(v[0]);
	/*if (k->e_length % 2 == 1)
		temp1 = k->e_length + 1;
	else
		temp1 = k->e_length;*/

	char* t1 = new char[stoi(v[0]) + 1];
	strcpy_s(t1, stoi(v[0]) + 1, v[1].c_str());
	d->a = t1;
	//cout << d->a << endl;

	d->p_length = stoi(v[2]);
	/*if (k->d_length % 2 == 1)
		temp1 = k->d_length + 1;
	else
		temp1 = k->d_length;*/

	char* t2 = new char[stoi(v[2]) + 1];
	strcpy_s(t2, stoi(v[2]) + 1, v[3].c_str());
	d->p = t2;
	//cout << d->p << endl;

	//k->n_length = stoi(v[4]);
	/*if (k->n_length % 2 == 1)
		temp1 = k->n_length + 1;
	else
		temp1 = k->n_length;*/
	/*
	char* t3 = new char[stoi(v[4]) + 1];
	strcpy_s(t3, stoi(v[4]) + 1, v[5].c_str());
	k->n = t3;
	cout << k->n << endl;
	*/
	return d;
}
