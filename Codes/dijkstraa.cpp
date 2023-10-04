#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int>> adj[100];
int dist[100], par[100];


void dijkstra(int source)
{
    priority_queue<pair<int,int>,
	vector<pair<int,int>>,greater<pair<int,int>>>pq;

    dist[source] = 0;
    pq.push({0,source});


    while(!pq.empty()){
        int dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for(auto it : adj[node]){
            int edgewt = it.second;
            int adjnode = it.first;

            if(dis + edgewt < dist[adjnode]){
                dist[adjnode] = dis + edgewt;
                pq.push(dist[adjnode], adjnode);
            }
        }
    }
}

int main()
{
    int n,edge;
    cin>>n>>edge;

    for(int i=0;i<edge;i++){
        int u,v,wt;
        cin>>u>>v>>wt;
        adj[u].push_back({v,wt});
        adj[v].push_back({u,wt});
    }

    for(int i=0;i<n;i++){
        dist[i] = 999999;
    }

    int source = 0;

    dijkstra(source);
}
