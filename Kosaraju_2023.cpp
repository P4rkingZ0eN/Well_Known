// Author : haruki291sa ( twitter : @291sa_ )
// Strongly Connected Component
// Kosaraju Algorithm
// Written in 19/02/2023 (DD/MM/YYYY)

#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
vector<vi>G,GT,SCC;
vector<bool>vis;
stack<int>f;
bool T;
void DFS(int x){
    vi g=(T)?GT[x]:G[x];
    for(int y:g){
        if(vis[y])continue;
        vis[y]=true;
        if(T)SCC.back().push_back(y);
        DFS(y);
    }
    if(!T)f.push(x);
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int V,E;cin>>V>>E;
    G.resize(V+1);GT.resize(V+1);
    T=false;
    for(int i=0;i<E;i++){
        int x,y;cin>>x>>y;
        G[x].push_back(y);
        GT[y].push_back(x);
    }
    vis=vector<bool>(V+1,false);
    for(int x=1;x<=V;x++){
        if(vis[x])continue;
        vis[x]=true;
        DFS(x);
    }
    T=true;
    vis=vector<bool>(V+1,false);
    while(!f.empty()){
        int x=f.top();f.pop();
        if(vis[x])continue;
        vis[x]=true;
        SCC.push_back({x});
        DFS(x);
    }
    cout<<SCC.size()<<"\n";
    for(vi &v:SCC)sort(v.begin(),v.end());
    sort(SCC.begin(),SCC.end());
    for(vi v:SCC){
        for(int x:v)cout<<x<<" ";
        cout<<"-1\n";
    }
    return 0;
}
