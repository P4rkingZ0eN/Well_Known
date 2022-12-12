#include <bits/stdc++.h>
using namespace std;
vector<vector<int> >G1,G2,Vd1,Vd2;
vector<int>dep1,dep2,dp,anc,S1,S2;
int rt1,rt2;

// Tree DP on f1
int f1(int cur){
    dp[cur]=1;
    for(int i=0;i<(int)G1[cur].size();i++){
        int nxt=G1[cur][i];
        if(anc[nxt])continue;
        anc[nxt]=cur;
        dp[cur]+=f1(nxt);
    }
    return dp[cur];
}

// Tree DP on f2
int f2(int cur){
    dp[cur]=1;
    for(int i=0;i<(int)G2[cur].size();i++){
        int nxt=G2[cur][i];
        if(anc[nxt])continue;
        anc[nxt]=cur;
        dp[cur]+=f2(nxt);
    }
    return dp[cur];
}

// Find Centroid
void findCentroid(int N){
    anc=dp=vector<int>(N+2,0);
    anc[1]=1;f1(1);
    vector<int>C1,C2;
    for(int i=1;i<=N;i++){
        bool flag=true;
        for(int j=0;j<(int)G1[i].size();j++){
            int nxt=G1[i][j];
            if(nxt==anc[i]){
                if(dp[1]-dp[i]>N/2)flag=false;
            }else if(dp[nxt]>N/2)flag=false;
        }
        if(flag)C1.push_back(i);
    }
    if((int)C1.size()>1){
        rt1=N+1;
        G1[C1[0]].push_back(rt1);
        G1[rt1].push_back(C1[0]);
        G1[C1[1]].push_back(rt1);
        G1[rt1].push_back(C1[1]);
    }else rt1=C1[0];
    anc=dp=vector<int>(N+2,0);
    anc[1]=1;f2(1);
    for(int i=1;i<=N;i++){
        bool flag=true;
        for(int j=0;j<(int)G2[i].size();j++){
            int nxt=G2[i][j];
            if(nxt==anc[i]){
                if(dp[1]-dp[i]>N/2)flag=false;
            }else if(dp[nxt]>N/2)flag=false;
        }
        if(flag)C2.push_back(i);
    }
    if((int)C2.size()>1){
        rt2=N+1;
        G2[C2[0]].push_back(rt2);
        G2[C2[1]].push_back(rt2);
        G2[rt2].push_back(C2[0]);
        G2[rt2].push_back(C2[1]);
    }else rt2=C2[0];
}

// Calculating the number of vertices that contain subtrees
void g(int N){
    anc=dp=vector<int>(N+3,0);
    anc[rt1]=rt1;f1(rt1);S1=dp;
    anc=dp=vector<int>(N+3,0);
    anc[rt2]=rt2;f2(rt2);S2=dp;
}

// calculating depth & making tuples
void bfs(int N){
    dep1=dep2=vector<int>(N+3,-1);
    queue<int>q1,q2;
    q1.push(rt1);q2.push(rt2);
    dep1[rt1]=0;dep2[rt2]=0;
    Vd1[0].push_back(S1[rt1]);Vd2[0].push_back(S2[rt2]);
    while(!q1.empty()){
        int x=q1.front();q1.pop();
        for(int i=0;i<(int)G1[x].size();i++){
            int y=G1[x][i];
            if(dep1[y]!=-1)continue;
            dep1[y]=dep1[x]+1;
            q1.push(y);
            Vd1[dep1[y]].push_back(S1[y]);
        }
    }
    while(!q2.empty()){
        int x=q2.front();q2.pop();
        for(int i=0;i<(int)G2[x].size();i++){
            int y=G2[x][i];
            if(dep2[y]!=-1)continue;
            dep2[y]=dep2[x]+1;
            q2.push(y);
            Vd2[dep2[y]].push_back(S2[y]);
        }
    }
}

bool Iso(){
    bool ret=true;
    for(int i=(int)Vd1.size()-1;i>=0;i--){
        sort(Vd1[i].begin(),Vd1[i].end());
        sort(Vd2[i].begin(),Vd2[i].end());
        if(Vd1[i].size()!=Vd2[i].size()){ret=false;break;}
        for(int j=0;j<(int)Vd1[i].size();j++){
            if(Vd1[i][j]!=Vd2[i][j]){ret=false;}
        }
        if(!ret)break;
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int V;cin>>V;
    G1.resize(V+2);G2.resize(V+2);
    Vd1.resize(V+2);Vd2.resize(V+2);
    for(int i=1;i<V;i++){
        int x,y;cin>>x>>y;
        G1[x].push_back(y);
        G1[y].push_back(x);
    }
    for(int i=1;i<V;i++){
        int x,y;cin>>x>>y;
        G2[x].push_back(y);
        G2[y].push_back(x);
    }
    findCentroid(V);
    g(V);bfs(V);
    bool res=Iso();
    cout<<(res?"Yes":"No");
    return 0;
}
