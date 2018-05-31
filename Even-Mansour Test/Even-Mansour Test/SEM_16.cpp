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
//	unsigned int s = p^k1;
//	unsigned int s1 = s / N, s2 = s%N;
//	unsigned int m = (a[s1] * N + a[s2]) ^ k2;
//	int c = a[s] ^ k2;
//	return c;
//}
//
//bool table_original_method(unsigned int &k_1,  vector<unsigned int>& pp, vector<unsigned>& delta) {  //�·���(��������Ϊ[0,plain))
//	map<unsigned int, unsigned int>  table;  //����ΪE(P)\oplus P==>p
//
//	for (int i = 0;i != pp.size();i++) {  //�������������Ķ�
//		unsigned p = pp[i];
//		unsigned c = EM(p);
//		table[p^c] = p;
//	}
//
//	for (int i = 0;i != delta.size();i++) {
//		unsigned x = delta[i];
//		unsigned pivot = a[x] ^ x;  //F(x)\oplus x
//		if (table.find(pivot) != table.end()) {
//			k_1 = table[pivot]^x;
//			if (k_1 == k1)
//				return true;
//		}
//	}
//	return false;
//}
//
//
//bool table_new_method(unsigned int &k_2, vector<unsigned int>& pp, vector<unsigned>& delta) {  //�·���(��������Ϊ[0,plain))
//	map<unsigned int, unsigned int>  table;  //����ΪE(P)\oplus P==>p
//
//	for (int i = 0;i != pp.size();i++) {  //�������������Ķ�
//		unsigned p = pp[i];
//		unsigned c = EM(p);
//		table[p^c] = c;
//	}
//
//	for (int i = 0;i != delta.size();i++) {
//		unsigned x = delta[i];
//		unsigned pivot = b[x] ^ x;  //F^{-1}(x)\oplus x
//		if (table.find(pivot) != table.end()) {
//			k_2 = table[pivot] ^ x;
//			if (k_2 == k2)
//				return true;
//		}
//	}
//	return false;
//}
//
//int main() {
//	for (int bound = 65535; bound < 65536; bound *= 2) { //�Ͻ�
//		srand(unsigned(time(0)));
//		int success_1 = 0, success_2 = 0;  //1��ʶ�Ϸ�����2��ʶ�·����ɹ�����
//		int count = 10000;
//		for (int i = 0;i != count;i++) {  //500���ԣ������������ʵ���ĳɹ���
//			permu();
//			for (int j = 0; j != N; j++) {
//				b[a[j]] = j;
//			}
//			//���¸�ֵk1,k2
//			k1 = rand() % N;
//			k2 = k1;  //SEM��Կ��ͬ
//
//			unsigned int k_1 = 0, k_2 = 0;
//			unsigned int  plain = 256;  //���ø������ĸ���
//			unsigned delta_num = 256;
//
//			vector<unsigned int> pp(plain, 0);
//			vector<unsigned> delta(delta_num, 0);
//
//			for (int i = 0;i != delta_num;i++)
//				delta[i] = i;  //deltaȡֵΪ0~255
//
//			permu_plain(pp, bound);  //���ɸ�������
//			
//
//			if (table_original_method(k_1, pp, delta))
//				success_1++;
//
//			if (table_new_method(k_2, pp, delta))
//				success_2++;
//		}
//		double per_1 = (double)success_1 / (double)count;
//		double per_2 = (double)success_2 / (double)count;
//		cout << bound << endl;
//		cout << per_1 << endl;
//		cout << per_2 << endl;
//	}
//	
//	system("pause"); 
//	
//	
//	
//}
//
