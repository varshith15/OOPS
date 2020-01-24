#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> iPair;
class Graph
{
    public:
    int V;
    list<int> *adj;
    Graph(int V);   
    void addEdge(int v, int w);
    void max(int src,int p[],int c[]);
    unordered_map<int,int> m;
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); 
}

void Graph::max(int src,int p[],int c[])
{
    priority_queue< iPair> pq;
    vector<int> dist(V, 0);
    pq.push(make_pair(p[m[src]]+c[m[src]]/2, src));
    dist[m[src]] = p[m[src]]+c[m[src]]/2;
    int parent[V];
    for(int i=0;i<V;i++){
        parent[i]=-1;
    }
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i);
            int weight = p[m[v]]+c[m[v]]/2;
            if (dist[v] < dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                parent[v]=u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    //for(int i=0;i){}
    int max=0,l;
    for(int i=0;i<V;i++){
        if(max<dist[i]){
            max=dist[i];
            l=i;
        }
    }
    //cout<<dist[l]<<endl;
    int q=0,w=0;
        stack<int> s;
        while(l!=-1){
            q+=p[m[l]];
            w+=c[m[l]];
            s.push(l);
            l=parent[l];
        }
    cout<<q<<" "<<w<<" "<<endl;
        while(!s.empty()){
            l=s.top();
            cout<<l<<" ";
            s.pop();
        }
}


int main() {
    int n;
    cin>>n;
    int id[n];
    int p[n];
    int c[n];
    Graph g(n);
    for(int i=0;i<n;i++){
        cin>>id[i]>>p[i]>>c[i];
        g.m[id[i]]=i;
    }
    bool a[n]={false};
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        g.addEdge(x,y);
        a[y]=true;
    }
    int root=-2;
    for(int i=0;i<n;i++){
        if(!a[i]){
            root=i;
            break;
        }
    }
    g.max(root,p,c);
    return 0;
}

