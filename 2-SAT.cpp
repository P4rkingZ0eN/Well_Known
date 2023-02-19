// Author : haruki291sa
// 2-SAT solver
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
vector<vi>G,GT,SCC;
vector<bool>vis;
stack<int>f;
vi cn;
bool T;
int N,M;
void DFS(int x){
    vi g=(T)?GT[x]:G[x];
    for(int y:g){
        if(vis[y])continue;
        vis[y]=true;
        if(T){
            SCC.back().push_back(y);
            cn[y]=SCC.size();
        }
        DFS(y);
    }
    if(!T)f.push(x);
}
int FALSE(int x){
    return x<=N?x+N:x-N;
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    cin>>N>>M;
    G.resize(2*N+1);GT.resize(2*N+1);
    cn=vi(2*N+1,0);
    T=false;
    for(int i=0;i<M;i++){
        int x,y;cin>>x>>y;
        if(x<0)x=N-x;
        if(y<0)y=N-y;
        G[FALSE(x)].push_back(y);
        GT[y].push_back(FALSE(x));
        G[FALSE(y)].push_back(x);
        GT[x].push_back(FALSE(y));
    }
    vis=vector<bool>(2*N+1,false);
    for(int x=1;x<=2*N;x++){
        if(vis[x])continue;
        vis[x]=true;
        DFS(x);
    }
    T=true;
    vis=vector<bool>(2*N+1,false);
    while(!f.empty()){
        int x=f.top();f.pop();
        if(vis[x])continue;
        vis[x]=true;
        SCC.push_back({x});
        cn[x]=SCC.size();
        DFS(x);
    }
    bool ans=true;
    for(int i=1;i<=N;i++)ans&=(cn[i]!=cn[i+N]);
    if(!ans){
        cout<<"There is no solution.";
        return 0;
    }
    for(int i=1;i<=N;i++)cout<<"x1: "<<(cn[i]>cn[i+N])<<"\n";
    return 0;
}
