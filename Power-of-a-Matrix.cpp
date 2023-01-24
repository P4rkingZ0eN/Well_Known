#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vl=vector<ll>;
const ll mod=1000;
int N;
vector<vl>f(vector<vl>A,vector<vl>B){
    vector<vl>T;T.resize(N);
    for(int i=0;i<N;i++){
        T[i].resize(N);
        for(int j=0;j<N;j++){
            T[i][j]=0;
            for(int k=0;k<N;k++){
                T[i][j]=(T[i][j]+A[i][k]*B[k][j]%mod)%mod;
            }
        }
    }
    return T;
}
vector<vl>po(vector<vl>M,ll r){
    vector<vl>ret=M;r--;
    while(r){
        if(r&1)ret=f(ret,M);
        r>>=1;M=f(M,M);
    }
    return ret;
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    ll B;cin>>N>>B;
    vector<vl>A(N,vl(N));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>A[i][j];
            A[i][j]%=mod;
        }
    }
    A=po(A,B);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)cout<<A[i][j]<<" ";
        cout<<"\n";
    }
    return 0;
}
