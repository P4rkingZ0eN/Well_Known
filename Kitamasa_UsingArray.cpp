#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ull=unsigned long long;
int tmp1[1003],tmp2[1003][1003];
struct Kitamasa{
	int MOD=1e9+7;
	unsigned SIZE=0;
	vector<int>a,c;

	void setting(vector<int>A,vector<int>C,int Mod){
		SIZE=A.size();
		a=A;c=C;
		MOD=Mod;
	}

	int calc_n(ull n){
		if(n<SIZE)return a[n];
		vector<bool>oper;
		while(n>2*SIZE){
			if(n&1){
				oper.push_back(true);
				n^=1;
			}else{
				oper.push_back(false);
				n>>=1;
			}
		}
		while(n>SIZE){
			oper.push_back(true);
			n--;
		}
		vector<int>C=c;
		reverse(oper.begin(),oper.end());
		for(bool op:oper){
			if(op){
				tmp1[0]=C[SIZE-1]*c[0]%MOD;
				for(unsigned i=1;i<SIZE;i++)tmp1[i]=(C[i-1]+C[SIZE-1]*c[i]%MOD)%MOD;
				for(unsigned i=0;i<SIZE;i++)C[i]=tmp1[i];
			}else{
				for(unsigned i=0;i<SIZE;i++)tmp2[0][i]=C[i];
				for(unsigned i=1;i<SIZE;i++){
					tmp2[i][0]=c[0]*tmp2[i-1][SIZE-1]%MOD;
					for(unsigned j=1;j<SIZE;j++)tmp2[i][j]=(tmp2[i-1][j-1]+tmp2[i-1][SIZE-1]*c[j]%MOD)%MOD;
				}
				for(unsigned i=0;i<SIZE;i++){
					C[i]=0;
					for(unsigned j=0;j<SIZE;j++)C[i]=(C[i]+tmp2[0][j]*tmp2[j][i]%MOD)%MOD;
				}
			}
		}
		int ret=0;
		for(unsigned i=0;i<SIZE;i++)ret=(ret+a[i]*C[i]%MOD)%MOD;

		return ret;
	}
};

Kitamasa Machine;
int main(){
	ios_base::sync_with_stdio(false);cin.tie(NULL);
	ull N,M;cin>>N>>M;
	vector<int>A(N,0),C(N,1);
	C[0]=1;A[0]=1;
	const int mod=1999;
	for(unsigned i=1;i<N;i++){
		A[i]=C[0];
		C[0]=(C[0]<<1)%mod;
	}
	Machine.setting(A,C,mod);
	cout<<Machine.calc_n(M);
	return 0;
}
