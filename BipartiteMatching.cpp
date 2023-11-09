#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<vector<int> >G;
vector<int>A,B;
vector<bool>vis;
int Match(int x){
	if(vis[x])return 0;
	vis[x]=1;
	for(int y:G[x]){
		if(B[y]==-1||Match(B[y])){
			A[x]=y;B[y]=x;
			return 1;
		}
	}
	return 0;
}
void solve(){
	cin>>n>>m;
	G=vector<vector<int> >(n+1);
	while(m--){
		int u,v;cin>>u>>v;
		G[u].push_back(v);
	}
	int ans=0;
	A=B=vector<int>(n+1,-1);
	for(int i=0;i<n;i++){
		vis=vector<bool>(n+1,false);
		ans+=Match(i);
	}
	cout<<ans<<"\n";
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(NULL);
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
