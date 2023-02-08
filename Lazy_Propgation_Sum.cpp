// Author: haruki291sa (Sora Sugiyama)

#include <bits/stdc++.h>
using namespace std;
using ll=long long;
ll seg[400003],lazy[400003],A[100003];
void Subroutine_of_Lazy(ll s,ll e,int pos){
    lazy[pos<<1]+=lazy[pos];
    lazy[(pos<<1)|1]+=lazy[pos];
    seg[pos<<1]+=((s+e)/2-s+1)*lazy[pos];
    seg[(pos<<1)|1]+=(e-(s+e)/2)*lazy[pos];
    lazy[pos]=0LL;
}
ll Count_with_SegmentTree(int S,int E,int s,int e,int pos){
    if(S>e||s>E)return 0LL;
    if(S<=s&&e<=E)return seg[pos];
    if(lazy[pos])Subroutine_of_Lazy(s,e,pos);
    return Count_with_SegmentTree(S,E,s,(s+e)>>1,pos<<1)+Count_with_SegmentTree(S,E,((s+e)>>1)+1,e,(pos<<1)|1);
}
void Lazy_Update(ll S,ll E,ll s,ll e,int pos,ll w){
    if(S>e||s>E)return;
    if(S<=s&&e<=E){
        lazy[pos]+=w;seg[pos]+=w*(e-s+1);
        while(pos>>=1)seg[pos]=seg[pos*2]+seg[pos*2+1];
        return;
    }
    if(lazy[pos])Subroutine_of_Lazy(s,e,pos);
    Lazy_Update(S,E,s,(s+e)>>1,pos<<1,w);
    Lazy_Update(S,E,((s+e)>>1)+1,e,(pos<<1)|1,w);
}
int main(){
    return 0;
}
/*
  Lazy_Update(S,E,s,e,pos,w) : Add w to the interval [S,E]
  Count_with_SegmentTree(S,E,s,e,pos) : sum of A_i, i in [S,E]
*/
  
  
