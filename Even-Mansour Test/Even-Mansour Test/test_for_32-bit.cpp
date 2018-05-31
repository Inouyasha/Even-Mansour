//#include <iostream>  
//#include <cstdlib>  
//#include <ctime>  
//#include<algorithm>
//#include<vector>
//#include<map>
//#include<random>
//#include<iterator>
//#include <stdio.h>
//#include <inttypes.h>
//#include<stdlib.h>
//
//using namespace std;
//
//#define ROUNDS 22
//
////speck ���룬��Ϊʵ���е��û�ʹ��
//static inline void speck_round(uint16_t& x, uint16_t& y, const uint16_t k)
//{
//	x = (x >> 7) | (x << (8 * sizeof(x) - 7)); // x = ROTR(x, 7)
//	x += y;
//	x ^= k;
//	y = (y << 2) | (y >> (8 * sizeof(y) - 2)); // y = ROTL(y, 2)
//	y ^= x;
//}
//
//static inline void speck_round_reverse(uint16_t& x, uint16_t& y, const uint16_t k)
//{
//	y = x^y;
//	y = (y >> 2) | (y << (8 * sizeof(y) - 2));  // y = ROTR(y, 2)
//
//	x ^= k;
//	x -= y;
//	x = (x << 7) | (x >> (8 * sizeof(x) - 7));  // x = ROTL(x, 7)		
//}
//
//
//
//
//
//
////permutation
////��������ļ���������32bits �����em
////��������̫������ʹ�÷ֳ�����16bits���ݵĶ�ά���ݷ�ʽ��˵��
//
//const unsigned N = 65536;
//
//vector<uint16_t> v_key;//����������Կ
//
//class text {  //���ｫһ��32bits���ݷָ�Ϊ����16bits����
//public:
//	uint16_t text1;
//	uint16_t text2;
//
//	text(uint16_t input1, uint16_t input2) :text1(input1), text2(input2) {}
//	text() :text1(0), text2(0) {}  //Ĭ��text�����㽨��
//
//	text& operator ^= (const text& a) {  //32bits���ݵ������
//		this->text1 ^= a.text1;
//		this->text2 ^= a.text2;
//		return *this;
//	}
//
//	bool operator ==(const text &a) {  //32bits���ݵ�ȡ��
//		if (this->text1 == a.text1 && this->text2 == a.text2)
//			return true;
//		else
//			return false;
//	}
//
//};
//
//bool operator <(const text &a, const text& b) {  //����<����map�ļ�Ϊ�ṹ��
//	if (a.text1 < b.text1)
//		return true;
//	else if (a.text1 == b.text1) {
//		if (a.text2 < b.text2)
//			return true;
//		else
//			return false;
//	}
//	else
//		return false;
//}
//
//text operator ^ (const text& a, const text& b) {  //32bits text���ݵ��������
//	text result = a;
//	result ^= b;
//	return result;
//}
//
//uint16_t key[4] = { 0x0100, 0x0908, 0x1110, 0x1918 };
//
//void encrypt(const text plaintext, text& ciphertext){  //32-bit speck
//	ciphertext.text1 = plaintext.text1;
//	ciphertext.text2 = plaintext.text2;
//	
//	v_key.clear();
//
//	uint16_t b = key[0];
//	uint16_t a0 = key[1];
//	uint16_t a1 = key[2];
//	uint16_t a2 = key[3];
//	
//	for (unsigned i = 0; i < ROUNDS; i++) {  //����22��
//		v_key.push_back(b);  //����Կ���棨�������ܣ�
//		
//		speck_round(ciphertext.text2, ciphertext.text1, b);
//		uint16_t a = a0;
//		speck_round(a, b, i);
//		a0 = a1;
//		a1 = a2;
//		a2 = a;
//	}
//
//	swap(ciphertext.text1, ciphertext.text2);
//}
//
//void decrypt(text& plaintext, const text& ciphertext) {
//	plaintext.text1 = ciphertext.text1;
//	plaintext.text2 = ciphertext.text2;
//
//	for (unsigned i = 0;i != ROUNDS;i++) {
//		uint16_t key = v_key[ROUNDS - i - 1];
//		speck_round_reverse(plaintext.text1, plaintext.text2, key);
//	}
//}
//
//
//
//text k1(0, 3), k2(0, 231); //32bits��Կ��ʼ��
//
//
//
//
//text randtext() {  //��32bit�����
//	text ret;
//	ret.text1 = rand() % N;
//	ret.text2 = rand() % N;
//	return ret;
//}
//
//text permu32(const text& input) {  //32bit�û�����ǰ16bit�û����ͺ�16bit�û���Ȼ��ƴ��һ��
//	text output(0, 0);
//
//	uint16_t key[4] = { 0x0100, 0x0908, 0x1110, 0x1918 };
//	
//
//	encrypt(input, output);
//	
//	//encrypt(input, output);  //�û�����Ϊinput�����Ϊoutput
//	return output;
//}
//
//text permu32_re(const text& input) {  //32bit�û�����
//	text output(0, 0);
//	
//	decrypt(output, input);
//
//	swap(output.text1, output.text2);
//	return output;
//}
//
//void permu_plain(vector<text>& pp, text space) {  //ppΪ���ķֲ������ķֲ�����[0,k)
//	text randtext(0, 0);  //���������������
//
//	srand(unsigned(time(0)));
//
//	for (int i = 0;i != pp.size();i++) {
//		if (space.text1 == 0) {  //������������ķֲ����λ16bitsΪ0���������ĸ�λҲΪ0
//			randtext.text1 = 0;
//			randtext.text2 = rand() % N;
//		}
//		else {
//			randtext.text1 = rand() % space.text1;
//			randtext.text2 = rand() % N;
//		}
//
//		pp[i].text1 = randtext.text1;  //������������Ĵ���
//		pp[i].text2 = randtext.text2;
//	}
//
//	return;
//}
//
//
//text em(const text& plain) {  //em(p)=f(p \oplus k1) \oplus k2
//	text cipher(0, 0);
//
//	text temp(0, 0);
//	temp = permu32(k1^plain);
//	cipher = temp ^ k2;
//
//	return cipher;
//}
//
//
//bool table_original_method(unsigned plain_num, const vector<text>& pp) {  //�·���,���ĸ���Ϊplain_num�����Ŀռ�Ϊpp
//	map<text, text>  table;  //����Ϊ��p^f^-1(c)��c��
//	text k_1(0, 0);
//
//	for (int i = 0; i != plain_num; i++) {  //��ÿ����֪������p^f^-1(c)��д�����У�����ײ
//		text p = pp[i];
//		text c = em(p);
//		text f_p = permu32(p);  //f_p=f(p)
//		text firstcord = c^f_p;  //���е�������
//
//
//		if (table.find(firstcord) == table.end()) {
//			table[firstcord] = p;
//		}
//		else {
//			k_1 = p ^ table[firstcord];
//			if (k_1 == k1)
//				return true;
//		}
//	}
//	return false;
//}
//
//bool table_new_method(unsigned plain_num, const vector<text>& pp) {  //�·���,���ĸ���Ϊplain_num�����Ŀռ�Ϊpp
//	map<text, text>  table;  //����Ϊ��p^f^-1(c)��c��
//	text k_2(0, 0);
//
//	for (int i = 0; i != plain_num; i++) {  //��ÿ����֪������p^f^-1(c)��д�����У�����ײ
//		text p = pp[i];
//		text c = em(p);
//		text f1_c = permu32_re(c);  //f1_c=f^-1(c)
//		text firstcord = p^f1_c;  //���е�������
//		text temp(0, 0);
//
//		if (table.find(firstcord) == table.end()) {
//			table[firstcord] = c;
//		}
//		else {
//			k_2 = c ^ table[firstcord];
//			if (k_2 == k2)
//				return true;
//			//return true;
//		}
//	}
//	return false;
//}
//
//
//
//
//int main() {
//	for (int bound1 = 1;bound1 <= 1;bound1 *= 4) {
//		srand(unsigned(time(0)));
//
//		text bound(bound1, 0);  //�Ͻ�(��65536��ʼ)
//
//		int success_1 = 0, success_2 = 0;  //1��ʶ�Ϸ�����2��ʶ�·����ɹ�����
//
//		int count = 500;  //ʵ�����
//
//		for (int i = 0;i != count;i++) {  //500���ԣ������������ʵ���ĳɹ���
//
//										  //���¸�ֵk1,k2
//			k1 = randtext();
//			k2 = randtext();
//
//			for (int i = 0;i != 4;i++) {
//				key[i] += 1;
//			}
//
//			unsigned int k_2 = 0;
//			unsigned int  plain = 65536;  //���ø������ĸ���
//
//			vector<text> pp(plain, text(0, 0));
//			permu_plain(pp, bound);  //���ɸ�������
//
//			if (table_original_method(plain, pp))
//				success_1++;
//
//			if (table_new_method(plain, pp))
//				success_2++;
//		}
//		double per_1 = (double)success_1 / (double)count;
//		double per_2 = (double)success_2 / (double)count;
//		cout << bound1 << endl;
//		cout << per_1 << endl;
//		cout << per_2 << endl;
//	}
//	
//
//	system("pause");
//}
