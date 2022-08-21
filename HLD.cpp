// Heavy Light Decomposition
// Author : Haruki Fukuhisa
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
struct Vertex{
    int pos,idx,anc,dep,hp;
    Vertex(){}
    Vertex(int pos,int idx,int anc,int dep,int hp):pos(pos),idx(idx),anc(anc),dep(dep),hp(hp){}
    void Print_Val(){
        printf("pos: %d  idx: %d  anc: %d  dep: %d  hp: %d\n",pos,idx,anc,dep,hp);
    }
};
vector<vi>G,C;
vector<Vertex>V;
int DFS(int x){
    V[x].hp=-1;
    int mx=-1,sum=1;
    for(int y:G[x]){
        if(V[y].anc!=-1)continue;
        V[y].anc=x;
        int w=DFS(y);
        sum+=w;
        if(mx<w){V[x].hp=y;mx=w;}
    }
    return sum;
}
void HLD(int x,int cc,int Dep){
    V[x].idx=(int)C[cc].size();
    V[x].pos=cc;
    V[x].dep=Dep;
    C[cc].push_back(x);
    if(V[x].hp!=-1)HLD(V[x].hp,cc,Dep);
    for(int y:G[x]){
        if(y==V[x].anc||y==V[x].hp)continue;
        HLD(y,y,Dep+1);
    }
}
int main(){
    int N;scanf("%d",&N);
    G.resize(N+1);C.resize(N+1);
    for(int i=1;i<N;i++){
        int x,y;scanf("%d%d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    V=vector<Vertex>(N+1,Vertex(0,0,-1,0,0));
    V[1].anc=1;
    DFS(1);
    HLD(1,1,1);
    return 0;
}
