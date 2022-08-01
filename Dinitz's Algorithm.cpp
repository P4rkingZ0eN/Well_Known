#include <bits/stdc++.h>
using namespace std;
int C[203][203],F[203][203],cV[203],L[203];
vector<int>G[203];
bool bfs(){
    memset(L,-1,sizeof(L));
    L[0]=0;
    queue<int>q;q.push(0);
    while(!q.empty()){
        int cur=q.front();q.pop();
        for(int i=0;i<(int)G[cur].size();i++){
            int nxt=G[cur][i];
            if(L[nxt]==-1&&C[cur][nxt]-F[cur][nxt]>0){
                L[nxt]=L[cur]+1;
                q.push(nxt);
            }
        }
    }
    return L[201]!=-1;
}
int dfs(int i,int flow){
    if(i==201)return flow;
    for(;cV[i]<(int)G[i].size();cV[i]++){
        int nxt=G[i][cV[i]];
        if(L[nxt]==L[i]+1&&C[i][nxt]-F[i][nxt]>0){
            int ret=dfs(nxt,min(C[i][nxt]-F[i][nxt],flow));
            if(ret>0){
                F[i][nxt]+=ret;
                F[nxt][i]-=ret;
                return ret;
            }
        }
    }
    return 0;
}
int main(){
    int N,M;scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++){
        G[0].push_back(i);
        G[i].push_back(0);
        int A;scanf("%d",&A);
        C[0][i]+=A;
    }
    for(int i=1;i<=M;i++){
        G[201].push_back(i+100);
        G[i+100].push_back(201);
        int B;scanf("%d",&B);
        C[i+100][201]+=B;
    }
    for(int i=1;i<=M;i++){
        for(int j=1;j<=N;j++){
            G[i+100].push_back(j);
            G[j].push_back(i+100);
            scanf("%d",&C[j][i+100]);
        }
    }
    int res=0;
    while(bfs()){
        memset(cV,0,sizeof(cV));
        while(1){
            int flow=dfs(0,2e9);
            if(!flow)break;
            res+=flow;
        }
    }
    printf("%d",res);
    return 0;
}
