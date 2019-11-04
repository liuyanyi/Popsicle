#pragma once
#include <bitset>
#include "Util.h"

//using namespace std;

const int row = 4, col = 4;
const int keyLength = 4;
const int Nr = 10;

class Aes_block_Operator {
public:
	//public 加密解密接口
	void encrypt(byteu in[row * col], byteu keys[row * col]);

	void decrypt(byteu in[row * col], byteu keys[row * col]);

private:

	word fB2Word(byteu b[], int N);

	word funcT(word w, int round);

	void keyExpansion(byteu mtx[row * col], word chain[keyLength * (Nr + 1)]);

	void subbytes(byteu mtx[row * col]);

	void inv_subbytes(byteu mtx[row * col]);

	void Reverse(byteu R[], int l, int r);

	void row_R(byteu mat[], int left, int start, int end);

	void shiftRows(byteu mtx[row * col]);

	void inv_shiftRows(byteu mtx[row * col]);

	byteu GFMul(byteu a, byteu b);

	void mixColumns(byteu mtx[row * col]);

	void inv_mixColumns(byteu mtx[row * col]);

	void addRoundKey(byteu mtx[row * col], word k[keyLength]);
};
