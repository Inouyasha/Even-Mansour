//#include <iostream>  
//#include <cstdlib>  
//#include <ctime>  
//#include<algorithm>
//#include<vector>
//#include<map>
//#include<random>
//#include<iterator>
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
//	unsigned int s = (p + k1) % N;
//	unsigned int m = (a[s] + k2) % N;
//	int c = (a[s] + k2) % N;
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
//			unsigned firstCord = (c + a[(del + N - p) % N]) % N;  //������������
//			if (table.find(firstCord) == table.end()) {
//				table[firstCord] = p;
//			}
//			else {
//				k_1 = (N - table[firstCord] + N- p + del) % N;
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
//			unsigned firstCord = (p + b[(N + del - c) % N]) % N;  //������������
//			if (table.find(firstCord) == table.end()) {
//				table[firstCord] = c;
//			}
//			else {
//				k_2 = (table[firstCord] +  c + N - del) % N;
//				if (k_2 == k2)
//					return true;
//			}
//		}
//	}
//	return false;
//}
//
//int main() {
//	clock_t start, end;
//	clock_t total_time = 0;
//
//	for (int bound = 65535; bound <= 65536; bound *= 4) { //�Ͻ�
//		srand(unsigned(time(0)));
//		int success_1 = 0, success_2 = 0;  //1��ʶ�Ϸ�����2��ʶ�·����ɹ�����
//		int count = 20000;
//		for (int i = 0;i != count;i++) {  //500���ԣ������������ʵ���ĳɹ���
//			permu();
//			for (int j = 0; j != N; j++) {
//				b[a[j]] = j;
//			}
//			//���¸�ֵk1,k2
//			k1 = rand() % N;
//			k2 = rand() % N;
//
//			unsigned int k_1 = 0, k_2 = 0;
//			unsigned int  plain = 128;  //���ø������ĸ���
//			unsigned delta_num = 8;
//
//			vector<unsigned int> pp(plain, 0);
//			vector<unsigned> delta(delta_num, 0);
//			
//
//			permu_plain(pp, bound);  //���ɸ�������
//			permu_plain(delta, 65536);
//			
//			start = clock();
//			if (table_original_method(k_1, pp, delta))
//				success_1++;
//
//			end = clock();
//			clock_t time = end - start;
//			total_time += time;
//
//			/*if (table_new_method(k_2, pp, delta))
//				success_2++;*/
//		}
//		/*double per_1 = (double)success_1 / (double)count;
//		double per_2 = (double)success_2 / (double)count;
//		cout << bound << endl;
//		cout << per_1 << endl;
//		cout << per_2 << endl;*/
//		double total_time_sec = (double)(total_time) / CLOCKS_PER_SEC;  //��������ʱ��
//
//		double per_1 = (double)success_1 / (double)count;
//
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
