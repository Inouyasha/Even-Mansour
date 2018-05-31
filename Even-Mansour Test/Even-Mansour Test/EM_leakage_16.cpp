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
//void permu_plain(vector<unsigned int>& pp, unsigned int k) {  //ppΪ���ķֲ������ķֲ�����[0,k)
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
//bool table_original_method(unsigned int &k_1,  vector<unsigned int>& pp, vector<unsigned>& delta) {  //�·���(��������Ϊ[0,plain))
//	map<unsigned, unsigned> plain_cipher;
//
//	for (int i = 0;i != pp.size();i++) {  //�������������Ķ�
//		unsigned p = pp[i];
//		unsigned c = EM(p);
//		plain_cipher[p] = c;
//	}
//
//	for (int i = 0; i != delta.size(); i++) {  //��ÿ����֪������P^F^-1(C)��д�����У�����ײ
//		map<unsigned int, unsigned int>  table;  //����Ϊ��P^F^-1(C)��C��
//
//		unsigned del = delta[i];
//		for (auto it = plain_cipher.begin();it != plain_cipher.end();it++) {
//			unsigned p = it->first, c = it->second;
//			unsigned firstCord = c ^ a[p ^ del];  //������������
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
//bool table_new_method(unsigned int &k_2, vector<unsigned int>& pp, vector<unsigned>& delta) {  //�·���(��������Ϊ[0,plain))
//	map<unsigned, unsigned> plain_cipher;
//
//	for (int i = 0;i != pp.size();i++) {  //�������������Ķ�
//		unsigned p = pp[i];
//		unsigned c = EM(p);
//		plain_cipher[p] = c;
//	}
//
//	for (int i = 0; i != delta.size(); i++) {  //��ÿ����֪������P^F^-1(C)��д�����У�����ײ
//		map<unsigned int, unsigned int>  table;  //����Ϊ��P^F^-1(C)��C��
//
//		unsigned del = delta[i];
//		for (auto it = plain_cipher.begin();it != plain_cipher.end();it++) {
//			unsigned p = it->first, c = it->second;
//			unsigned firstCord = p ^ b[c ^ del];  //������������
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
//	//int leakage_num = 0;  //й¶��λbit��
//
//	for (int leakage_num = 0; leakage_num <= 14; leakage_num += 2) {
//		srand(unsigned(time(0)));
//		int success_1 = 0, success_2 = 0;  //1��ʶ�Ϸ�����2��ʶ�·����ɹ�����
//		int count = 10000;
//
//		clock_t start, end;
//		clock_t total_time = 0;
//
//		
//
//		for (int i = 0;i != count;i++) {  //10000���ԣ������������ʵ���ĳɹ���
//			permu();
//			for (int j = 0; j != N; j++) {
//				b[a[j]] = j;
//			}
//			//���¸�ֵk1,k2
//			k1 = rand() % N;
//			k2 = rand() % N;
//
//			int rate = pow(2, 16 - leakage_num);  //��������һ����Ϊx||y��ʽ,2^(n-k)
//			int leakage_k1 = k1 / rate;  //й¶��Կx
//			 
//			unsigned int k_1 = 0, k_2 = 0;
//			unsigned int  plain = pow(2, (16 - leakage_num) / 2);  //���ø������ĸ���2^(n-leakage/2)
//
//
//			vector<unsigned int> pp(plain, 0);
//			vector<unsigned> delta(1, 0);
//			delta[0] = leakage_k1 * rate;
//
//			int bound = rate;
//			permu_plain(pp, bound);  //���ɸ�������
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
//		double total_time_sec = (double)(total_time) / CLOCKS_PER_SEC;  //��������ʱ��
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
