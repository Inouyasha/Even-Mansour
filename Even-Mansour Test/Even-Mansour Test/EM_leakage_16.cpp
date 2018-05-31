//#include <iostream>  
//#include <cstdlib>  
//#include <ctime>  
//#include<algorithm>
//#include<vector>
//#include<map>
//#include<random>
//#include<iterator>
//#include<math.h>
//#include<time.h>
//
//using namespace std;
//
//#define N 65536
//
//
//
//vector<unsigned int> a(N, 0), b(N, 0);  //a-->F, b-->F^-1
//
//unsigned int k1 = 999, k2 = 0;//key
//
//void permu() {//permutation
//	for (int i = 0;i != N;i++) {	
//		a[i] = i;
//	}
//	for (int i = N - 1;i != 0;i--) {
//		int j = rand() % i;
//		swap(a[i], a[j]);
//	}
//	return;
//}
//
//void permu_plain(vector<unsigned int>& pp, unsigned int k) {  //pp为明文分布，明文分布区间[0,k)
//	unsigned int randtemp;
//	srand(unsigned(time(0)));
//	for (int i = 0;i != pp.size();i++) {
//		randtemp = rand() % k;
//		pp[i] = randtemp;
//	}
//	return;
//}
//
//
//unsigned int EM(unsigned int p) {
//	unsigned int s = p^k1;
//	unsigned int s1 = s / N, s2 = s%N;
//	unsigned int m = (a[s1] * N + a[s2]) ^ k2;
//	int c = a[s] ^ k2;
//	return c;
//}
//
//bool table_original_method(unsigned int &k_1,  vector<unsigned int>& pp, vector<unsigned>& delta) {  //新方法(给定明文为[0,plain))
//	map<unsigned, unsigned> plain_cipher;
//
//	for (int i = 0;i != pp.size();i++) {  //建立表保存明密文对
//		unsigned p = pp[i];
//		unsigned c = EM(p);
//		plain_cipher[p] = c;
//	}
//
//	for (int i = 0; i != delta.size(); i++) {  //对每个已知明文求P^F^-1(C)，写到表中，找碰撞
//		map<unsigned int, unsigned int>  table;  //表里为（P^F^-1(C)，C）
//
//		unsigned del = delta[i];
//		for (auto it = plain_cipher.begin();it != plain_cipher.end();it++) {
//			unsigned p = it->first, c = it->second;
//			unsigned firstCord = c ^ a[p ^ del];  //保存表的首坐标
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
//
//bool table_new_method(unsigned int &k_2, vector<unsigned int>& pp, vector<unsigned>& delta) {  //新方法(给定明文为[0,plain))
//	map<unsigned, unsigned> plain_cipher;
//
//	for (int i = 0;i != pp.size();i++) {  //建立表保存明密文对
//		unsigned p = pp[i];
//		unsigned c = EM(p);
//		plain_cipher[p] = c;
//	}
//
//	for (int i = 0; i != delta.size(); i++) {  //对每个已知明文求P^F^-1(C)，写到表中，找碰撞
//		map<unsigned int, unsigned int>  table;  //表里为（P^F^-1(C)，C）
//
//		unsigned del = delta[i];
//		for (auto it = plain_cipher.begin();it != plain_cipher.end();it++) {
//			unsigned p = it->first, c = it->second;
//			unsigned firstCord = p ^ b[c ^ del];  //保存表的首坐标
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
//int main() {
//	//int leakage_num = 0;  //泄露高位bit数
//
//	for (int leakage_num = 0; leakage_num <= 14; leakage_num += 2) {
//		srand(unsigned(time(0)));
//		int success_1 = 0, success_2 = 0;  //1标识老方法，2标识新方法成功次数
//		int count = 10000;
//
//		clock_t start, end;
//		clock_t total_time = 0;
//
//		
//
//		for (int i = 0;i != count;i++) {  //10000测试，用来计算随机实例的成功性
//			permu();
//			for (int j = 0; j != N; j++) {
//				b[a[j]] = j;
//			}
//			//重新赋值k1,k2
//			k1 = rand() % N;
//			k2 = rand() % N;
//
//			int rate = pow(2, 16 - leakage_num);  //用来划分一个数为x||y形式,2^(n-k)
//			int leakage_k1 = k1 / rate;  //泄露密钥x
//			 
//			unsigned int k_1 = 0, k_2 = 0;
//			unsigned int  plain = pow(2, (16 - leakage_num) / 2);  //设置给定明文个数2^(n-leakage/2)
//
//
//			vector<unsigned int> pp(plain, 0);
//			vector<unsigned> delta(1, 0);
//			delta[0] = leakage_k1 * rate;
//
//			int bound = rate;
//			permu_plain(pp, bound);  //生成给定明文
//
//			start = clock();
//
//			if (table_original_method(k_1, pp, delta))
//				success_1++;
//
//			end = clock();
//			clock_t time = end - start;
//			total_time += time;
//
//		}
//		double total_time_sec = (double)(total_time) / CLOCKS_PER_SEC;  //程序运行时间
//		
//		double per_1 = (double)success_1 / (double)count;
//
//		cout << leakage_num << endl;
//		cout << per_1 << endl;
//		cout << total_time_sec << endl;
//	}
//	
//	system("pause"); 
//	
//	
//	
//}
//
