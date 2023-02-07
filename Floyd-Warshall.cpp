#include <bits/stdc++.h>
using namespace std;
using ll=long long;
vector<vector<ll> >Floyd_Warshall(vector<vector<ll> >W){
    vector<vector<ll> >D=W;
    int n=W.size()-1;
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                D[i][j]=min(D[i][j],D[i][k]+D[k][j]);
            }
        }
    }
    return D;
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int n,m;cin>>n>>m;
    vector<vector<ll> >d(n+1,vector<ll>(n+1,1e18));
    for(int i=1;i<=n;i++)d[i][i]=0;
    // Input
    while(m--){
        ll a,b,c;cin>>a>>b>>c;
        d[a][b]=min(d[a][b],c);
    }
    d=Floyd_Warshall(d);

    // Printing
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)cout<<(d[i][j]==1e18?0:d[i][j])<<" ";
        cout<<"\n";
    }

    return 0;
}
