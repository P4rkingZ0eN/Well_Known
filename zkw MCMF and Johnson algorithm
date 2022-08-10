#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >pq;
const int sz=805;
int C[sz][sz],F[sz][sz],W[sz][sz],h[sz],dist[sz],L[sz];
bool A[sz];
vector<int>G[sz];
void Johnson(){
    vector<bool>inq(sz,false);
    fill(h,h+803,2e9);
    fill(dist,dist+803,2e9);
    inq[0]=true;
    queue<int>q;q.push(0);
    while(!q.empty()){
        int cur=q.front();q.pop();
        inq[cur]=false;
        for(int i=0;i<(int)G[cur].size();i++){
            int nxt=G[cur][i];
            if(C[cur][nxt]>0&&h[nxt]>h[cur]+W[cur][nxt]){
                h[nxt]=h[cur]+W[cur][nxt];
                if(!inq[nxt]){
                    inq[nxt]=true;
                    q.push(nxt);
                }
            }
        }
    }
    for(int i=0;i<=801;i++){
        for(int j=0;j<(int)G[i].size();j++){
            int k=G[i][j];
            if(C[i][k]>0)W[i][k]+=h[i]-h[k];
        }
    }
    pq.push({0,0});dist[0]=0;
    while(!pq.empty()){
        pair<int,int>cur=pq.top();pq.pop();
        if(dist[cur.se]<cur.fi)continue;
        for(int i=0;i<(int)G[cur.se].size();i++){
            int nxt=G[cur.se][i];
            if(C[cur.se][nxt]<=0||dist[nxt]<=dist[cur.se]+W[cur.se][nxt])continue;
            dist[nxt]=dist[cur.se]+W[cur.se][nxt];
            pq.push({dist[nxt],nxt});
        }
    }
    for(int i=0;i<=801;i++)dist[i]+=h[801]-h[0];
}
bool upd(){
    int mn=2e9;
    for(int i=0;i<=801;i++){
        if(!A[i])continue;
        for(int j=0;j<(int)G[i].size();j++){
            int k=G[i][j];
            if(C[i][k]>0&&(!A[k]))mn=min(mn,dist[i]+W[i][k]-dist[k]);
        }
    }
    if(mn==2e9)return false;
    for(int i=0;i<=801;i++){
        if(!A[i])dist[i]+=mn;
    }
    return true;
}
int dfs(int cur,int flow){
    A[cur]=true;
    if(cur==801)return flow;
    for(;L[cur]<(int)G[cur].size();L[cur]++){
        int nxt=G[cur][L[cur]];
        if(!A[nxt]&&dist[nxt]==dist[cur]+W[cur][nxt]&&C[cur][nxt]>0){
            int ret=dfs(nxt,min(flow,C[cur][nxt]));
            if(ret){
                C[cur][nxt]-=ret;C[nxt][cur]+=ret;
                return ret;
            }
        }
    }
    return 0;
}
int main(){
    int N,M;scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++){
        C[0][i]=1;
        G[0].push_back(i);
        G[i].push_back(0);
    }
    for(int i=1;i<=M;i++){
        C[i+400][801]=1;
        G[801].push_back(i+400);
        G[i+400].push_back(801);
    }
    for(int i=1;i<=N;i++){
        int n;scanf("%d",&n);
        while(n--){
            int u,w;scanf("%d%d",&u,&w);
            G[i].push_back(u+400);
            G[u+400].push_back(i);
            C[i][u+400]=1;
            W[i][u+400]=w;
            W[u+400][i]=-w;
        }
    }
    int res=0,cnt=0;
    Johnson();
    while(1){
        memset(A,false,sizeof(A));
        memset(L,0,sizeof(L));
        int now=0;
        while(1){
            now=dfs(0,2e9);
            if(now==0)break;
            res+=dist[801]*now;
            cnt+=now;
            memset(A,false,sizeof(A));
        }
        if(!upd())break;
    }
    printf("%d\n%d",cnt,res);
}
