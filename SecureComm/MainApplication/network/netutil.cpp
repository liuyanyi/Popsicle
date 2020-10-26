#include "netutil.h"
#include "../security/Util.h"
#include "QDebug"
#include "messageheader.h"
#include "netsignal.h"

#include "WinSock2.h"
#include "security/controller.h"
#pragma comment(lib, "ws2_32.lib")

dh_key* dh = nullptr;

NetUtil::NetUtil()
{
}

std::string NetUtil::buildTictoc(int mode)
{
	//return "";
	//std::string result;
	std::string result;
	//result.reserve(600);
	switch (mode)
	{
	case TIC:
		result = result + inner_network::MSG_TIC;
		break;
	case TOC:
		result = result + inner_network::MSG_TOC;
		break;
	}

	char name_buf[128];
	gethostname(name_buf, 128);

	//    std::string name = std::string(name_buf);
	std::string name = name_buf;

	result += lengthToHex(name.length());
	//NetSignal::emitNotify(QString(name.length()));
	//qDebug()<<QString::fromStdString(result);

	result += name;

	key_pair* pair = Util::get_rsa_key("");
	result += lengthToHex(pair->n_length);
	result += pair->n;
	//qDebug()<<QString::fromStdString(result);

	return result;
}

std::string NetUtil::buildDicdoc(int mode)
{
	std::string result;
	//result.reserve(600);
	switch (mode)
	{
	case DIC:
		result = result + inner_network::MSG_DIC;
		break;
	case DOC:
		result = result + inner_network::MSG_DOC;
		break;
	}
	if (dh == nullptr)
		dh = controller::dh_generator("");
	//qDebug() << "DH A:  " << QString::fromStdString(dh->a);
	//qDebug() << "DH P:  " << QString::fromStdString(dh->p);
	//qDebug() << "DH Ya:  " << QString::fromStdString(dh);
	//qDebug() << "Ya:    " << QString::fromStdString(dh->ya);
	if (dh == nullptr)
		return "";

	std::string yaLocked = controller::rsa_encrypt(dh->ya, "", SIGN);
	//qDebug() << "YaL:    " << QString::fromStdString(yaLocked);
	result += yaLocked;
	return result;
}

std::vector<std::string> NetUtil::unpackTictoc(std::string msg)
{
	std::vector<std::string> result;
	int nameLength = lengthToInt(msg.substr(1, 3));
	//qDebug()<<nameLength;
	//qDebug()<<QString::fromStdString(msg.substr(4,nameLength));
	result.push_back(msg.substr(4, nameLength));
	//int rsaLength = lengthToInt(msg.substr(4 + nameLength, 3));
	result.push_back(msg.substr(6 + nameLength));
	//qDebug() <<"rsakey:  "<< QString::fromStdString(msg.substr(6 + nameLength, rsaLength));
	return result;
}

std::string NetUtil::unpackDictoc(std::string msg, std::string ip)
{
	std::lock_guard<std::mutex> lk(l_AllUserMutex);
	std::string cipher = msg.substr(1);
	std::string plain = controller::rsa_sign_decrypt(cipher, "", l_AllPublicKey[ip]);

	//qDebug() << QString::fromStdString(l_AllPublicKey[ip]);
	//qDebug() << "Ybl:    " << QString::fromStdString(cipher);
	//qDebug() << "Yb:    " << QString::fromStdString(plain);

	if (dh == nullptr)
		dh = controller::dh_generator("");
	std::string aes = controller::dh_operator(dh, plain);
	//key_pair *  pair = Util::get_rsa_key("");
	//qDebug() << QString::fromStdString(pair->n);
	return aes;
}

std::string NetUtil::lengthToHex(int length)
{
	char temp[4];
	//qDebug()<<length;
	temp[0] = intToChar(length / 256);
	temp[1] = intToChar((length - (length / 256) * 256) / 16);
	temp[2] = intToChar((length - (length / 256) * 256) % 16);
	temp[3] = 0;
	//qDebug()<<QString::fromStdString(temp)<<"???";

	return temp;
}

int NetUtil::lengthToInt(std::string length)
{
	int result = 0;
	//qDebug()<<QString::fromStdString(length)<<"FFF";
	result += charToInt(length[0]) * 256;
	result += charToInt(length[1]) * 16;
	result += charToInt(length[2]);
	//qDebug()<<result<<"XXX";
	return result;
}

char NetUtil::intToChar(const int i)
{
	int c;
	//qDebug()<<i<<"++";
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

int NetUtil::charToInt(const char c)
{
	int i;
	if (c >= 'a')
	{
		i = c - 87;
	}
	else
	{
		i = c - 48;
	}
	//qDebug()<<i<<"++";
	return i;
}
