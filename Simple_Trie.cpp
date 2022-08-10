#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int> >vp[100003];
int cnt=1,len;
char S[100003];
void Insert(int i,int n){
    bool flag=true;
    for(int j=0;j<(int)vp[i].size();j++){
        int nxt=vp[i][j].first,w=vp[i][j].second;
        if(S[n]==w){
            Insert(nxt,n+1);
            flag=false;
            break;
        }
    }
    if(flag){
        int k=i;
        for(int j=n;j<len;j++){
            vp[k].push_back({++cnt,S[j]});
            k=cnt;
        }
    }
}
bool Search(int i,int n){
    if(n==len)return true;
    for(int j=0;j<(int)vp[i].size();j++){
        int nxt=vp[i][j].first,w=vp[i][j].second;
        if(S[n]==w)return Search(nxt,n+1);
    }
    return false;
}
int main(){
    while(1){
        int Q;
        scanf("%d%s",&Q,S);
        if(Q!=1&&Q!=2)break;
        len=strlen(S);
        if(Q==1)Insert(1,0);else printf("%s\n",Search(1,0)?"Yes":"No");
    }
    return 0;
}
