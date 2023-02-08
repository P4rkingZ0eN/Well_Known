#include <bits/stdc++.h>
using namespace std;
using ll=long long;
ll seg[4000003],lazy[4000003],A[1000003],res;
void Subroutine_of_Lazy(int s,int e,int pos){
    lazy[pos<<1]+=lazy[pos];
    lazy[(pos<<1)|1]+=lazy[pos];
    seg[pos<<1]+=lazy[pos];
    seg[(pos<<1)|1]+=lazy[pos];
    lazy[pos]=0LL;
}
void Minimum_SegmentTree(int k,int S,int E,int s,int e,int pos){
    if(S>e||s>E)return;
    if(S<=s&&e<=E){
        res=min(res,seg[pos]);
        return;
    }
    Subroutine_of_Lazy(s,e,pos);
    Minimum_SegmentTree(k,S,E,s,(s+e)>>1,pos<<1);
    Minimum_SegmentTree(k,S,E,((s+e)>>1)+1,e,(pos<<1)|1);
}
void Lazy_Update(int S,int E,int s,int e,int pos,ll w){
    if(S>e||s>E)return;
    if(S<=s&&e<=E){
        lazy[pos]+=w;seg[pos]+=w;
        while(pos>>=1)seg[pos]=min(seg[pos*2],seg[pos*2+1]);
        return;
    }
    if(lazy[pos])Subroutine_of_Lazy(s,e,pos);
    Lazy_Update(S,E,s,(s+e)>>1,pos<<1,w);
    Lazy_Update(S,E,((s+e)>>1)+1,e,(pos<<1)|1,w);
}
int main(){
    return 0;
}
