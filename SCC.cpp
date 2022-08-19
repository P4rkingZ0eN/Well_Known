// Author : Haruki Fukuhisa
// Reference : Introduction to Algorithm 3rd Edition p.629 (Kosaraju Algorithm)
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
inline bool cmp(vi a,vi b){
    return a[0]<b[0];
}
vector<vi>G,GT,SCC;
vector<bool>vv;
stack<int>f;
bool T;
vi scc;
void DFS(int x){
    vi &g=(T)?G[x]:GT[x];
    for(int i=0;i<(int)g.size();i++){
        int y=g[i];
        if(vv[y])continue;
        vv[y]=true;
        if(!T)scc.push_back(y);
        DFS(y);
    }
    if(T)f.push(x);
}
int main(){
    int V,E;scanf("%d%d",&V,&E);
    G.resize(V+1);GT.resize(V+1);
    T=true;
    for(int i=0;i<E;i++){
        int x,y;scanf("%d%d",&x,&y);
        G[x].push_back(y);
        GT[y].push_back(x);
    }
    vv=vector<bool>(V+1,false);
    for(int x=1;x<=V;x++){
        if(vv[x])continue;
        vv[x]=true;
        DFS(x);
    }
    T=false;
    vv=vector<bool>(V+1,false);
    while(!f.empty()){
        scc.clear();
        int x=f.top();f.pop();
        if(vv[x])continue;
        vv[x]=true;
        scc.push_back(x);
        DFS(x);
        SCC.push_back(scc);
    }
    printf("%d\n",(int)SCC.size());
    for(int i=0;i<(int)SCC.size();i++)sort(SCC[i].begin(),SCC[i].end());
    sort(SCC.begin(),SCC.end(),cmp);
    for(int i=0;i<(int)SCC.size();i++){
        for(int j=0;j<(int)SCC[i].size();j++)printf("%d ",SCC[i][j]);
        printf("-1\n");
    }
    return 0;
}
