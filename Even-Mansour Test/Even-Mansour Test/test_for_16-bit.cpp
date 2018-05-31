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
////permutation
//
//#define N 65536
//
//
//
////vector<unsigned int> b(N, 0);//permutation
////vector<vector<unsigned int>> a(N, b);
//vector<unsigned int> a(N, 0), b(N, 0);  //a-->F, b-->F^-1
////vector<vector<unsigned int>> *a = new vector<vector<unsigned int>>(2, b);
////unsigned int  **a = new unsigned int*[N];
//
//unsigned int k1 = 999, k2 = 0;//key
//
//void permu() {//permutation
//	for (int i = 0;i != N;i++) {	
//		a[i] = i;
//	}
//	//cout << N << endl;
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
//	//unsigned int s1 = s / N, s2 = s%N;
//	//unsigned int m = (a[s1] * N + a[s2]) ^ k2;
//	int c = a[s] ^ k2;
//	return c;
//}
//
////bool table(unsigned int &k_1, unsigned int delta, unsigned int plain) {//1 table find collison
////	map<unsigned int, int>  table;
////	//vector<int> b(N, -1);
////	for (int i = 0;i != plain;i++) {
////		unsigned int temp = i^delta;
////		unsigned int i1 = temp / N, i2 = temp%N;
////		unsigned int m1 = EM(i) ,m2= (a[i1] * N + a[i2]);
////		unsigned int m = m1^m2;
////		if (table[m] !=0 ) {//map的默认值为0
////			if (table[m] == -1) {//取0时我们置为-1，此时还原为0
////				//k_1 = delta^i;
////				int t = i^delta;
////				unsigned int t1 = t / N, t2 = t%N;
////				k_1 = EM(0) ^ (a[t1] * N + a[t2]);
////			}
////			else {
////				//k_1 = table[m] ^ delta^i;
////				int t = i^delta;
////				unsigned int t1 = t/N, t2 = t%N;
////				k_1 = EM(table[m]) ^ (a[t1] * N + a[t2]);
////			}
////			if(k2==k_1)
////				cout << k_1 << endl;
////			//return true;
////		}
////		else {
////			if (i == 0)
////				table[m] = -1;
////			else
////				table[m] = i;
////		}
////	}
////	if (k_1 != 0)
////		return true;
////	return false;
////}
//
//bool table_original_method(unsigned int &k_1, unsigned int plain, vector<unsigned int>& pp) {  //新方法(给定明文为[0,plain))
//	map<unsigned int, unsigned int>  table;  //表里为（P^F^-1(C)，C）
//	for (int i = 0; i != plain; i++) {  //对每个已知明文求P^F^-1(C)，写到表中，找碰撞
//		unsigned int p = pp[i];
//		unsigned int c = EM(p);
//		unsigned int f_p = a[p];  //f_p=F(P)
//		unsigned int firstCord = c^f_p;  //表中的首坐标
//
//		if (table[firstCord] == 0) {
//			table[firstCord] = p;
//		}
//		else {
//			k_1 = p ^ table[firstCord];
//			//cout << k_2 << endl;
//			if (k_1 == k1)
//				return true;
//		}
//	}
//	return false;
//
//}
//
//bool table_new_method(unsigned int &k_2,  unsigned int plain, vector<unsigned int>& pp) {  //新方法(给定明文为[0,plain))
//	map<unsigned int, unsigned int>  table;  //表里为（P^F^-1(C)，C）
//	for (int i = 0; i != plain; i++) {  //对每个已知明文求P^F^-1(C)，写到表中，找碰撞
//		unsigned int p = pp[i];
//		unsigned int c = EM(p);
//		unsigned int f1_c = b[c];  //f1_c=F^-1(C)
//		unsigned int firstCord = p^f1_c;  //表中的首坐标
//		
//		if (table[firstCord] == 0) {
//			table[firstCord] = c;
//		}
//		else {
//			k_2 = c ^ table[firstCord];
//			//cout << k_2 << endl;
//			if (k_2 == k2)
//				return true;
//		}
//	}
//	return false;
//
//}
//
//
////bool attack(int &b1) {
////	unsigned int delta = (1<<13)+4096, plain = 4096, k_1=0;
////	for (int i = 1<<13;i != delta;i++) {
////		if (table(k_1, i, plain)) {
////			b1 = k_1;
////			return true;
////		}		
////	}
////	return false;
////	
////}
//
//int main() {
//	srand(unsigned(time(0)));
//	
//	//求F（置换）
//	//permu();
//
//	////求F^-1
//	//for (int i = 0; i != N; i++) {
//	//	b[a[i]] = i;
//	//}
//
//	int k = 32768;  //上界
//
//	int success_1 = 0, success_2 = 0;  //1标识老方法，2标识新方法成功次数
//	int count = 10000;
//	for (int i = 0;i != count;i++) {  //500测试，用来计算随机实例的成功性
//		permu();
//
//		//求F^-1
//		for (int j = 0; j != N; j++) {
//			b[a[j]] = j;
//		}
//									  //重新赋值k1,k2
//		k1 = rand() % N;
//		k2 = rand() % N;
//
//		unsigned int k_2 = 0;
//		unsigned int  plain = 256;  //设置给定明文个数
//
//		vector<unsigned int> pp(plain, 0);
//		permu_plain(pp, k);  //生成给定明文
//		
//		if (table_original_method(k_2, plain, pp))
//			success_1++;
//
//		if (table_new_method(k_2, plain, pp))
//			success_2++;
//	}
//	double per_1 = (double)success_1 / (double)count;
//	double per_2 = (double)success_2 / (double)count;
//	cout << per_1 << endl;
//	cout << per_2 << endl;
//	//for (int j = 0;j != 20;j++) {
//	//	//k_2为可能的密钥
//	//	int success = 0;  //成功次数
//	//	int count = 1000;
//	//	for (int i = 0;i != count;i++) {  //500测试，用来计算随机实例的成功性
//	//									  //充值k1,k2
//	//		k1 = rand() % N;
//	//		k2 = rand() % N;
//
//	//		unsigned int k_2 = 0;
//	//		unsigned int  plain = 512;  //设置给定明文个数
//
//	//		vector<unsigned int> pp(plain, 0);
//	//		permu_plain(pp, k);  //生成给定明文
//
//	//		if (table_new(k_2, plain))
//	//			success++;
//	//	}
//
//	//	double per = (double)success / (double)count;
//	//	cout << per << endl;
//	//}
//	//
//	
//	system("pause"); 
//	
//	
//	
//}
//
////#define N 32768//N=1<<15
////
////void initialize(vector<int> &a) {
////	std::random_device rd;
////	std::mt19937 mt(rd());
////
////	for (int i = 0;i != a.size();i++) {
////		a[i] = mt() % N;
////	}
////	return;
////}
////
////double test() {
////	vector<int> a1(32, 0), a2, a3(32, 0);
////	initialize(a1);
////	copy(a1.begin(), a1.end(), back_inserter(a2));
////	initialize(a3);
////	vector<int> st(N, 0);
////	for (int i = 0;i != a1.size();i++) {
////		for (int j = 0;j != a2.size();j++) {
////			for (int k = 0;k != a3.size();k++) {
////				int temp = (a1[i] ^ a2[j] ^ a3[k]) % N;
////				st[temp] ++;
////			}
////		}
////	}
////	int count1 = 0, count2 = 0, count3 = 0;
////	for (int i = 0;i != st.size();i++) {
////		if(st[i]>0)
////			count1 ++;
////	}
////	for (int i = 0;i != st.size();i++) {
////		if (st[i] > 1) {
////			count2 ++;
////			
////		}
////		if (st[i] > 2)
////			count3++;
////			
////	}
////	cout << (double)count2 / (double)N << endl;//重复超过1次的
////	cout << (double)count3 / (double)N << endl;//重复超过2次的
////	double ret = (double)count1 / (double)N;
////	return ret;
////}
////
////int main() {
////	srand(unsigned(time(0)));
////	double ret = test();
////	cout << ret << endl;
////	system("pause");
////}
//
//
////覆盖率测试
////const int n = 65536;  
////
////
////void initialize(vector<unsigned int> &a) {
////	std::random_device rd;
////	std::mt19937 mt(rd());
////
////	for (int i = 0;i != a.size();i++) {
////		a[i] = mt() % n;
////	}
////	return;
////}
////
////
////double test1() {
////	int n = 256;
////	vector<unsigned int> a1(n, 0), a2(n/(n), 0);
////	/*
////	for (int i = 0;i != n;i++) {
////		a1[i] = i;
////	}
////	*/
////	initialize(a1);
////	initialize(a2);
////	copy(a1.begin(), a1.end(), back_inserter(a2));
////	initialize(a3);
////	vector<int> st(n, 0);
////	for (int i = 0;i != a1.size();i++) {
////		for (int j = 0;j != a2.size();j++) {
////			
////				int temp = (a1[i] ^ a2[j] ) % n;
////				st[temp] ++;
////			
////		}
////	}
////	int count1 = 0, count2 = 0, count3 = 0;
////	for (int i = 0;i != st.size();i++) {
////		if (st[i]>0)
////			count1++;
////	}
////	for (int i = 0;i != st.size();i++) {
////		if (st[i] > 1) {
////			count2++;
////
////		}
////		if (st[i] > 2)
////			count3++;
////
////	}
////	cout << (double)count2 / (double)n << endl;//重复超过1次的
////	cout << (double)count3 / (double)n << endl;//重复超过2次的
////	double ret = (double)count1 / (double)n;
////	return ret;
////}
////
////double test2() {
////	int n = sqrt(n);
////	vector<unsigned int> a1(n, 0), a2(n, 0);
////	
////	initialize(a1);
////	initialize(a2);
////	copy(a1.begin(), a1.end(), back_inserter(a2));
////	initialize(a3);
////	vector<int> st(n, 0);
////	for (int i = 0;i != a1.size();i++) {
////		for (int j = 0;j != a2.size();j++) {
////
////			int temp = (a1[i] ^ a2[j]) % n;
////			st[temp] ++;
////
////		}
////	}
////	int count1 = 0, count2 = 0, count3 = 0;
////	for (int i = 0;i != st.size();i++) {
////		if (st[i]>0)
////			count1++;
////	}
////	for (int i = 0;i != st.size();i++) {
////		if (st[i] > 1) {
////			count2++;
////
////		}
////		if (st[i] > 2)
////			count3++;
////
////	}
////	cout << (double)count2 / (double)n << endl;//重复超过1次的
////	cout << (double)count3 / (double)n << endl;//重复超过2次的
////	double ret = (double)count1 / (double)n;
////	return ret;
////}
////
////int main() {
////	srand(unsigned(time(0)));
////	double ret = test1();
////	cout << ret << endl;
////	system("pause");
////}
