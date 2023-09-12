// BOJ 1395

#include <bits/stdc++.h>
using namespace std;
using ull=unsigned long long;
ull seg[6253],lazy[6253];

void h(int s,int e,int pos){
	if(s>e)return;
	int l=s-((s>>6)<<6),r=e-((e>>6)<<6);
	ull bit=0ULL;
	int sh=r-l+1;
	if(sh==64)bit--;else bit=(((1ULL<<sh)-1)<<l);
	seg[pos]^=bit;
}
void g(int s,int e,int pos,int S,int E){
	if(!lazy[pos])return;
	int ee=(s+e)>>1,ss=((s+e)>>1)+1;
	if(((ss-1)>>6)==((e-1)>>6)){
		h(ss-1,e-1,(pos<<1)|1);
	}else{
		lazy[(pos<<1)|1]^=1;
		seg[(pos<<1)|1]=(e-ss+1)-seg[(pos<<1)|1];
	}
	if(((s-1)>>6)==((ee-1)>>6)){
		h(s-1,ee-1,pos<<1);
	}else{
		lazy[pos<<1]^=1;
		seg[pos<<1]=(ee-s+1)-seg[pos<<1];
	}
	lazy[pos]=0;
}

ull ST(int s,int e,int pos,int S,int E){
	if(S>e||s>E)return 0;
	if(((s-1)>>6)<((e-1)>>6))g(s,e,pos,S,E);
	if(((e-1)>>6)==((s-1)>>6)){
		int l=max(s,S)-1,r=min(e,E)-1;
		l-=((l>>6)<<6),r-=((r>>6)<<6);
		ull bit=0ULL;
		int sh=r-l+1;
		if(sh==64)bit--;else bit=(((1ULL<<sh)-1)<<l);
		ull tmp=(seg[pos]&bit);
		return __builtin_popcountll(tmp);
	}
	if(S<=s&&e<=E)return seg[pos];
	return ST(s,(s+e)>>1,pos<<1,S,E)+ST(((s+e)>>1)+1,e,(pos<<1)|1,S,E);
}

void lazy_prop(int s,int e,int pos,int S,int E){
	if(S>e||s>E)return;
	if(((s-1)>>6)<((e-1)>>6))g(s,e,pos,S,E);
	if(((e-1)>>6)==((s-1)>>6)){
		int l=max(s,S)-1,r=min(e,E)-1;
		l-=((l>>6)<<6),r-=((r>>6)<<6);
		int tmp=__builtin_popcountll(seg[pos]);
		int sh=r-l+1;
		ull bit=0ULL;
		if(sh==64)bit--;else bit=(((1ULL<<sh)-1)<<l);
		seg[pos]^=bit;
		int p=pos,dw=__builtin_popcountll(seg[pos])-tmp;
		while(p>>=1)seg[p]+=dw;
		return;
	}
	if(S<=s&&e<=E){
		int p=pos,dw=(e-s+1)-(seg[pos]<<1);
		lazy[pos]^=1;
		seg[pos]=(e-s+1)-seg[pos];
		while(p>>=1)seg[p]+=dw;
		return;
	}
	lazy_prop(s,(s+e)>>1,pos<<1,S,E);
	lazy_prop(((s+e)>>1)+1,e,(pos<<1)|1,S,E);
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(NULL);
	int N,M;cin>>N>>M;
	int st=1;while(st<N)st<<=1;
	while(M--){
		int O,S,T;cin>>O>>S>>T;
		if(O)cout<<ST(1,st,1,S,T)<<"\n";else lazy_prop(1,st,1,S,T);
	}
	return 0;
}
