#pragma once
#include "Util.h"
#include <string>

//using namespace std;

constexpr auto AES_ECB = 1;
constexpr auto AES_CBC = 2;

constexpr auto ENCRYPT = 1;
constexpr auto SIGN    = 2;

constexpr auto FILE_ENCRYPT = 1;
constexpr auto FILE_DECRYPT = 2;

class controller {
  public:
    /**
	 * \brief AES加密
	 * \param plain_text 明文 Hex字符串
	 * \param key 密钥 Hex字符串
	 * \param mode 选择模式 aes_ecb/aes_cbc
	 * \return 密文 Hex字符串
	 */
    static string aes_encrypt(const string &plain_text, const string &key, int mode);
    static void   aes_encrypt(unsigned char *plain_text, const string &key, int length);
    /**
	* \brief AES解密
	* \param cipher_text 密文 Hex字符串
	* \param key 密钥 Hex字符串
	* \param mode 选择模式 aes_ecb/aes_cbc
	* \return 明文 Hex字符串
	*/
    static string aes_decrypt(const string &cipher_text, const string &key, int mode);

    static void aes_decrypt(unsigned char *text, const string &key, int length);

    /**
	* \brief RSA加密
	* \param plain_text 明文 Hex字符串
	* \param key_file_path 密钥文件名
	* \param mode 加密或签名
	* \return 密文 Base64字符串
	*/
    static string rsa_encrypt(string plain_text, string key_file_path, int mode);

    /**
	* \brief RSA解密
	* \param cipher_text 明文 Base64字符串
	* \param key_file_path 密钥文件名
	* \param mode 加密或签名
	* \return 密文 Hex字符串
	*/
    static string rsa_decrypt(string cipher_text, string key_file_path, int mode);
    static string rsa_sign_decrypt(string cipher_text, string key_file_path, string n);

    /**
	* \brief DH密钥交换,生成y
	* \param pa_file_path 素数文件名
	* \return DH KEY
	*/
    static dh_key *dh_generator(string pa_file_path);

    static string dh_operator(dh_key *d, string ybc);

    /**
	 * \brief MD5加密
	 * \param plain_text 明文 Hex字符串
	 * \return 128位密文 Hex字符串
	 */
    static string md5_generator(string plain_text);

    /**
	 * \brief 文件解密
	 * \param input_file_path 输入文件路径（已加密）
	 * \param output_file_path 输出文件路径（解密）
	 * \param mode 加密或解密
	 * \return 是否成功
	 */
    static bool file_handle(wstring input_file_path, wstring output_file_path, string key, int mode);

  private:
};
