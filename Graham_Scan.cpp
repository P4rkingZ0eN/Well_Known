// Author : haruki291sa
// Graham scan

#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using ll=long long;
using pii=pair<ll,ll>;
pii P[100003];
ll dist(pii a,pii b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
ll ccw(const pii &a,const pii &b,const pii &c){
	ll tmp=a.x*b.y+b.x*c.y+c.x*a.y-a.y*b.x-b.y*c.x-c.y*a.x;
	if(tmp<0)return -1;
	else if(tmp>0)return 1;
	else return 0;
}
inline bool cmp(const pii &a,const pii &b){
	return ccw(P[1],a,b)>0||(ccw(P[1],a,b)==0&&dist(a,P[1])<dist(b,P[1]));
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int N;cin>>N;
    for(int i=1;i<=N;i++)cin>>P[i].x>>P[i].y;
    sort(P+1,P+1+N);
    sort(P+2,P+1+N,cmp);
    vector<ll>hull={1,2};
    for(int i=3;i<=N;i++){
        while((int)hull.size()>=2){
            ll a,b;
            b=hull.back();
            hull.pop_back();
            a=hull.back();
            if(ccw(P[a],P[b],P[i])>0){
                hull.push_back(b);
                break;
            }
        }
        hull.push_back(i);
    }
    cout<<hull.size();
    return 0;
}
