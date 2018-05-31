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
////speck 代码，作为实验中的置换使用
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
////这个测试文件用来测试32bits 输入的em
////由于数字太大，这里使用分成两个16bits数据的二维数据方式来说明
//
//const unsigned N = 65536;
//
//vector<uint16_t> v_key;//用来保存密钥
//
//class text {  //这里将一个32bits数据分割为两个16bits数据
//public:
//	uint16_t text1;
//	uint16_t text2;
//
//	text(uint16_t input1, uint16_t input2) :text1(input1), text2(input2) {}
//	text() :text1(0), text2(0) {}  //默认text，方便建表
//
//	text& operator ^= (const text& a) {  //32bits数据的自异或
//		this->text1 ^= a.text1;
//		this->text2 ^= a.text2;
//		return *this;
//	}
//
//	bool operator ==(const text &a) {  //32bits数据的取等
//		if (this->text1 == a.text1 && this->text2 == a.text2)
//			return true;
//		else
//			return false;
//	}
//
//};
//
//bool operator <(const text &a, const text& b) {  //重载<用于map的键为结构体
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
//text operator ^ (const text& a, const text& b) {  //32bits text数据的异或运算
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
//	for (unsigned i = 0; i < ROUNDS; i++) {  //进行22轮
//		v_key.push_back(b);  //将密钥保存（用来解密）
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
//text k1(0, 3), k2(0, 231); //32bits密钥初始化
//
//
//
//
//text randtext() {  //求32bit随机数
//	text ret;
//	ret.text1 = rand() % N;
//	ret.text2 = rand() % N;
//	return ret;
//}
//
//text permu32(const text& input) {  //32bit置换即对前16bit置换，和后16bit置换，然后拼在一起
//	text output(0, 0);
//
//	uint16_t key[4] = { 0x0100, 0x0908, 0x1110, 0x1918 };
//	
//
//	encrypt(input, output);
//	
//	//encrypt(input, output);  //置换输入为input，输出为output
//	return output;
//}
//
//text permu32_re(const text& input) {  //32bit置换的逆
//	text output(0, 0);
//	
//	decrypt(output, input);
//
//	swap(output.text1, output.text2);
//	return output;
//}
//
//void permu_plain(vector<text>& pp, text space) {  //pp为明文分布，明文分布区间[0,k)
//	text randtext(0, 0);  //用来生成随机明文
//
//	srand(unsigned(time(0)));
//
//	for (int i = 0;i != pp.size();i++) {
//		if (space.text1 == 0) {  //如果给定的明文分布界高位16bits为0，生成明文高位也为0
//			randtext.text1 = 0;
//			randtext.text2 = rand() % N;
//		}
//		else {
//			randtext.text1 = rand() % space.text1;
//			randtext.text2 = rand() % N;
//		}
//
//		pp[i].text1 = randtext.text1;  //将生成随机明文传入
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
//bool table_original_method(unsigned plain_num, const vector<text>& pp, const vector<text>& delta) {  //新方法,明文个数为plain_num，明文空间为pp	
//	map<text, text>  plain_cipher;
//
//	for (int i = 0;i != pp.size();i++) {  //建立表保存明密文对
//		text p = pp[i];
//		text c = em(p);
//		plain_cipher[p] = c;
//	}
//
//	text k_1(0, 0);
//
//	for (int i = 0; i != delta.size(); i++) {  //对每个已知明文求P^F^-1(C)，写到表中，找碰撞
//		map<text, text>  table;  //表里为（P^F^-1(C)，C）
//
//		text del = delta[i];
//		for (auto it = plain_cipher.begin();it != plain_cipher.end();it++) {
//			text p = it->first, c = it->second;
//			text firstCord = c ^ permu32(p ^ del);  //保存表的首坐标
//			if (table.find(firstCord) == table.end()) {
//				table[firstCord] = p;
//			}
//			else {
//				k_1 = table[firstCord] ^ p ^ del;
//				if (k_1 == k1)
//					return true;
//			}
//		}
//	}
//	return false;
//}
//
//bool table_new_method(unsigned plain_num, const vector<text>& pp, const vector<text>& delta) {  //新方法,明文个数为plain_num，明文空间为pp
//	map<text, text>  plain_cipher;
//
//	for (int i = 0;i != pp.size();i++) {  //建立表保存明密文对
//		text p = pp[i];
//		text c = em(p);
//		plain_cipher[p] = c;
//	}
//
//	text k_2(0, 0);
//
//	for (int i = 0; i != delta.size(); i++) {  //对每个已知明文求P^F^-1(C)，写到表中，找碰撞
//		map<text, text>  table;  //表里为（P^F^-1(C)，C）
//
//		text del = delta[i];
//		for (auto it = plain_cipher.begin();it != plain_cipher.end();it++) {
//			text p = it->first, c = it->second;
//			text firstCord = p ^ permu32_re(c ^ del);  //保存表的首坐标
//			if (table.find(firstCord) == table.end()) {
//				table[firstCord] = c;
//			}
//			else {
//				k_2 = table[firstCord] ^ c ^ del;
//				if (k_2 == k2)
//					return true;
//			}
//		}
//	}
//	return false;
//}
//
//
//
//
////int main() {
////	for (int bound1 = 65535;bound1 < 65536;bound1*=4) {
////		srand(unsigned(time(0)));
////
////		text bound(bound1, 65535);  //上界(从16384开始)
////
////		int success_1 = 0, success_2 = 0;  //1标识老方法，2标识新方法成功次数
////
////		int count = 500;  //实验次数
////
////		clock_t start, end;
////		clock_t total_time = 0;
////
////		for (int i = 0;i != count;i++) {  //500测试，用来计算随机实例的成功性
////
////										  //重新赋值k1,k2
////			k1 = randtext();
////			k2 = randtext();
////
////			for (int i = 0;i != 4;i++) {
////				key[i] += 1;
////			}
////
////			unsigned int k_2 = 0;
////			unsigned int  plain = 16384;  //设置给定明文个数
////			
////
////			vector<text> pp(plain, text(0, 0));
////			permu_plain(pp, bound);  //生成给定明文
////
////			unsigned delta_num = 32;
////			vector<text> delta(delta_num, text(0, 0));
////			permu_plain(delta, text(65535, 65535));
////
////			start = clock();
////
////			if (table_original_method(plain, pp, delta))
////				success_1++;
////
////			end = clock();
////			clock_t time = end - start;
////			total_time += time;
////
////			/*if (table_new_method(plain, pp, delta))
////				success_2++;*/
////		}
////		double total_time_sec = (double)(total_time) / CLOCKS_PER_SEC;  //程序运行时间
////
////		double per_1 = (double)success_1 / (double)count;
////		double per_2 = (double)success_2 / (double)count;
////		cout << bound1 << endl;
////		cout << per_1 << endl;
////		cout << per_2 << endl;
////		cout << total_time_sec << endl;
////	}
////	
////
////	system("pause");
////}
