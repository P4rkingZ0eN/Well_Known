#include <bits/stdc++.h>
using namespace std;
const int sz=803;
vector<int>vi[sz];
int C[sz][sz],F[sz][sz],W[sz][sz];
int main(){
    int N,M;scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++){
        C[0][i]=1;
        vi[0].push_back(i);
        vi[i].push_back(0);
    }
    for(int i=1;i<=M;i++){
        C[i+400][801]=1;
        vi[i+400].push_back(801);
        vi[801].push_back(i+400);
    }
    for(int i=1;i<=N;i++){
        int n;scanf("%d",&n);
        while(n--){
            int u,w;scanf("%d%d",&u,&w);
            vi[i].push_back(u+400);
            vi[u+400].push_back(i);
            W[i][u+400]=w;
            W[u+400][i]=-w;
            C[i][u+400]=1;
        }
    }
    int res=0,cnt=0;
    while(1){
        vector<int>anc(sz,-1),dist(sz,2e9);
        vector<bool>visit(sz,false);
        dist[0]=0;visit[0]=true;
        queue<int>q;q.push(0);
        while(!q.empty()){
            int cur=q.front();q.pop();
            visit[cur]=false;
            for(int i=0;i<(int)vi[cur].size();i++){
                int nxt=vi[cur][i];
                if(C[cur][nxt]-F[cur][nxt]>0&&dist[nxt]>dist[cur]+W[cur][nxt]){
                    dist[nxt]=dist[cur]+W[cur][nxt];
                    anc[nxt]=cur;
                    if(!visit[nxt]){
                        q.push(nxt);
                        visit[nxt]=true;
                    }
                }
            }
        }
        if(anc[801]==-1)break;
        int flow=2e9;
        for(int i=801;i!=0;i=anc[i])flow=min(flow,C[anc[i]][i]-F[anc[i]][i]);
        for(int i=801;i!=0;i=anc[i]){
            res+=flow*W[anc[i]][i];
            F[anc[i]][i]+=flow;
            F[i][anc[i]]-=flow;
        }
        cnt+=flow;
    }
    printf("%d\n%d",cnt,res);
    return 0;
}
