// Reference : Justice Hui
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >pq;
// Set your size of graph
const int sz=2005;
int src,sink;
long long C[sz][sz],W[sz][sz],h[sz],dist[sz],L[sz];
bool A[sz];
vector<int>G[sz];
void Johnson(){
    vector<bool>inq(sz,false);
    fill(h,h+sz,9e17);
    fill(dist,dist+sz,9e17);
    inq[0]=true;
    queue<int>q;q.push(src);
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
    for(int i=0;i<sz;i++){
        for(int j=0;j<(int)G[i].size();j++){
            int k=G[i][j];
            if(C[i][k]>0)W[i][k]+=h[i]-h[k];
        }
    }
    pq.push({0,src});dist[src]=0;
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
    for(int i=0;i<sz;i++)dist[i]+=h[sink]-h[src];
}
bool upd(){
    long long mn=9e17;
    for(int i=0;i<sz;i++){
        if(!A[i])continue;
        for(int j=0;j<(int)G[i].size();j++){
            int k=G[i][j];
            if(C[i][k]>0&&(!A[k]))mn=min(mn,dist[i]+W[i][k]-dist[k]);
        }
    }
    if(mn==9e17)return false;
    for(int i=0;i<sz;i++){
        if(!A[i])dist[i]+=mn;
    }
    return true;
}
long long dfs(int cur,long long flow){
    A[cur]=true;
    if(cur==sink)return flow;
    for(;L[cur]<(int)G[cur].size();L[cur]++){
        int nxt=G[cur][L[cur]];
        if(!A[nxt]&&dist[nxt]==dist[cur]+W[cur][nxt]&&C[cur][nxt]>0){
            long long ret=dfs(nxt,min(flow,C[cur][nxt]));
            if(ret){
                C[cur][nxt]-=ret;C[nxt][cur]+=ret;
                return ret;
            }
        }
    }
    return 0;
}
int main(){
    //make your flow network
    src=1,sink=N+1000;
    long long res=0,cnt=0;
    Johnson();
    while(1){
        memset(A,false,sizeof(A));
        memset(L,0,sizeof(L));
        long long now=0;
        while(1){
            now=dfs(src,9e17);
            if(now==0)break;
            res+=dist[sink]*now;
            cnt+=now;
            memset(A,false,sizeof(A));
        }
        if(!upd())break;
    }
    printf("%lld",res);
}
