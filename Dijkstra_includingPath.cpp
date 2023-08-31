#include <bits/stdc++.h>
using namespace std;
using ll=long long;
vector<vector<pair<int,ll> > >G;
bool broken[1003][1003];
pair<vector<ll>,vector<pair<int,int> > >Dijkstra(int src,int sink,bool addPath){
	vector<ll>dist(G.size()+3,9e18);
	vector<int>anc(G.size()+3,0);
	priority_queue<pair<ll,int> >pq;
	pq.push({0,src});dist[src]=0;
	while(!pq.empty()){
		pair<ll,int>u=pq.top();pq.pop();
		if(-u.first>dist[u.second])continue;
		for(auto v:G[u.second]){
			if(broken[v.first][u.second])continue;
			if(dist[v.first]>v.second-u.first){
				dist[v.first]=v.second-u.first;
				anc[v.first]=u.second;
				pq.push({u.first-v.second,v.first});
			}
		}
	}
	if(!addPath)return {dist,vector<pair<int,int> >()};
	vector<pair<int,int> >path;
	int t=sink;
	while(anc[t]){
		path.push_back({anc[t],t});
		t=anc[t];
	}
	reverse(path.begin(),path.end());
	return {dist,path};
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(NULL);
	return 0;
}
