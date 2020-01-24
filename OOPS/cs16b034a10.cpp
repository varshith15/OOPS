#include <bits/stdc++.h>
using namespace std;

#define DBL_MAX1 1000001.0

typedef pair<float,int> ip;

class graph{            //graph class
	public:
	int v;
	graph(int v);          //constructor
    vector<vector<pair<int,float> > > adj;  //adjacency list using vector of vectors 
	void addedge(int x,int y,float wt);    //adding edge
	void min_time(int s);                  //shortedt path from source vertex s using diskstras
	void update_network(int s,float m);    //updating the graph
	void top_k(int c,int k);               //printing top-k vertices from source vertex s
	void pairwise_dist(int c1,int c2);     //floyd-warshal algorithm
	vector<int> cat[257];                  //array of vectors for storing catagories
	bool flag=true;            
	vector<vector<float> > dis;            
	vector<vector<int> > next;
};

graph::graph(int v){
	this->v=v;
    adj.resize(v);
}

void graph::addedge(int x,int y,float wt){
	adj[x].push_back(make_pair(y,wt));
}

void graph:: min_time(int s){
	priority_queue<ip,vector<ip>,greater<ip> > pq;
	vector<float> dis1(v,DBL_MAX1);
	pq.push(make_pair(0.0,s));
	dis1[s]=0.0;
	while(!pq.empty()){
		int u=pq.top().second;
		pq.pop();
		for(auto it=adj[u].begin();it!=adj[u].end();it++){
			int i=(*it).first;
			float wt= (*it).second;
			if(dis1[i]>dis1[u]+wt){
				dis1[i]=dis1[u]+wt;
				pq.push(make_pair(dis1[i],i));
			}
		}
	}
	for(int i=0;i<v;i++){
		if(dis1[i]!=DBL_MAX1){
            cout<<setprecision(3)<<dis1[i]<<" ";
		}
		else {
            cout<<"-1.000 ";
		}
	}
	cout<<endl;
}

void graph::update_network(int s,float m){
	priority_queue<ip,vector<ip>,greater<ip> > pq;
	vector<float> dis1(v,DBL_MAX1);
	pq.push(make_pair(0.0,s));
	dis1[s]=0.0;
	while(!pq.empty()){
		int u=pq.top().second;
		pq.pop();
		for(auto it=adj[u].begin();it!=adj[u].end();it++){
			int i=(*it).first;
			float wt= (*it).second;
			if(dis1[i]>dis1[u]+wt){
				dis1[i]=dis1[u]+wt;
				pq.push(make_pair(dis1[i],i));
			}
		}
	}
	for(auto it=adj[s].begin();it!=adj[s].end();it++){
		if(dis1[(*it).first]>m){
			(*it).second=m;
			dis1[(*it).first]=m;
            flag=true;
		}
	}
	for(int j=0;j<v;j++){
		if(dis1[j]>m){
			addedge(s,j,m);
            flag=true;
		}
	}
}

bool compare(pair<int,int> &p1,pair<int,int> &p2){
	if(p1.first==p2.first){
		return p1.second<p2.second;
	}
	return p1.first>p2.first;
}

void graph::top_k(int c,int k){
    pair<int, int> em = {0, 0};
	vector<pair<int, int>> feq(v, em);
	for(int i=0;i<cat[c].size();i++){
		for(auto it=adj[cat[c][i]].begin();it!=adj[cat[c][i]].end();it++){
			feq[(*it).first].first++;
            feq[(*it).first].second = (*it).first;
		}
	}
	sort(feq.begin(),feq.end(),compare);
    for(int i=0;i<k;i++){
        if(feq[i].first == 0) {
            break;
        }
        cout<<(feq[i].second+1)<<" ";
    }
	cout<<endl;
}

void graph::pairwise_dist(int c1,int c2){
	if(flag){
        dis=vector<vector<float> > (v,vector<float>(v,DBL_MAX1));
	    next=vector<vector<int> > (v,vector<int>(v,-1));
        for(int i=0;i<v;i++){
		    for(auto it=adj[i].begin();it!=adj[i].end();it++){
                int k=(*it).first;
                dis[i][k]=(*it).second;
                next[i][k]=k;
            }
        }
		for(int k=0;k<v;k++){
			for(int i=0;i<v;i++){
				for(int j=0;j<v;j++){
					if(dis[i][j]>(dis[i][k]+dis[k][j])){
						dis[i][j]=dis[i][k]+dis[k][j];
						next[i][j]=next[i][k];
                        flag=false;
					}
		            else if(dis[i][j]==dis[i][k]+dis[k][j] && next[i][k]<next[i][j]){
		                next[i][j]=next[i][k];
                        flag=false;
		            }
				}
			}
		}
	}
	for(int i=0;i<cat[c1].size();i++){
		for(int j=0;j<cat[c2].size();j++){
            int a=cat[c1][i],b=cat[c2][j];    
			cout<<a+1<<" "<<b+1<<"\t";
            if(dis[a][b]==DBL_MAX1){
                cout<<"-1"<<endl;
            }
            else{
                cout<<a+1<<" ";
				while(a!=b){
					a=next[a][b];
                    cout<<a+1<<" ";
				}
				cout<<endl;
            }
		}
	}
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed;
	int n,l;
	cin>>n>>l;
	graph g1(n);
	for(int i=0;i<n;i++){
		int x;
		cin>>x;
		g1.cat[x].push_back(i);	
	}
	for(int i=0;i<l;i++){
		int x,y;
        float wt;
		cin>>x>>y>>wt;
		g1.addedge(x-1,y-1,wt);
	}
	string s;
	while(cin>>s){
		if(s=="sssp"){
			int x;
			cin>>x;
			g1.min_time(x-1);
		}
		else if(s=="apsp"){
			int x,y;
			cin>>x>>y;
			g1.pairwise_dist(x,y);
		}
		else if(s=="update"){
			int x;
            float y;
			cin>>x>>y;
			g1.update_network(x-1,y);
		}
		else{
			int x,y;
			cin>>x>>y;
			g1.top_k(x,y);
		}
	}
	return 0;
}#include <bits/stdc++.h>
using namespace std;

#define DBL_MAX1 1000001.0

typedef pair<float,int> ip;

class graph{            //graph class
	public:
	int v;
	graph(int v);          //constructor
    vector<vector<pair<int,float> > > adj;  //adjacency list using vector of vectors 
	void addedge(int x,int y,float wt);    //adding edge
	void min_time(int s);                  //shortedt path from source vertex s using diskstras
	void update_network(int s,float m);    //updating the graph
	void top_k(int c,int k);               //printing top-k vertices from source vertex s
	void pairwise_dist(int c1,int c2);     //floyd-warshal algorithm
	vector<int> cat[257];                  //array of vectors for storing catagories
	bool flag=true;            
	vector<vector<float> > dis;            
	vector<vector<int> > next;
};

graph::graph(int v){
	this->v=v;
    adj.resize(v);
}

void graph::addedge(int x,int y,float wt){
	adj[x].push_back(make_pair(y,wt));
}

void graph:: min_time(int s){
	priority_queue<ip,vector<ip>,greater<ip> > pq;
	vector<float> dis1(v,DBL_MAX1);
	pq.push(make_pair(0.0,s));
	dis1[s]=0.0;
	while(!pq.empty()){
		int u=pq.top().second;
		pq.pop();
		for(auto it=adj[u].begin();it!=adj[u].end();it++){
			int i=(*it).first;
			float wt= (*it).second;
			if(dis1[i]>dis1[u]+wt){
				dis1[i]=dis1[u]+wt;
				pq.push(make_pair(dis1[i],i));
			}
		}
	}
	for(int i=0;i<v;i++){
		if(dis1[i]!=DBL_MAX1){
            cout<<setprecision(3)<<dis1[i]<<" ";
		}
		else {
            cout<<"-1.000 ";
		}
	}
	cout<<endl;
}

void graph::update_network(int s,float m){
	priority_queue<ip,vector<ip>,greater<ip> > pq;
	vector<float> dis1(v,DBL_MAX1);
	pq.push(make_pair(0.0,s));
	dis1[s]=0.0;
	while(!pq.empty()){
		int u=pq.top().second;
		pq.pop();
		for(auto it=adj[u].begin();it!=adj[u].end();it++){
			int i=(*it).first;
			float wt= (*it).second;
			if(dis1[i]>dis1[u]+wt){
				dis1[i]=dis1[u]+wt;
				pq.push(make_pair(dis1[i],i));
			}
		}
	}
	for(auto it=adj[s].begin();it!=adj[s].end();it++){
		if(dis1[(*it).first]>m){
			(*it).second=m;
			dis1[(*it).first]=m;
            flag=true;
		}
	}
	for(int j=0;j<v;j++){
		if(dis1[j]>m){
			addedge(s,j,m);
            flag=true;
		}
	}
}

bool compare(pair<int,int> &p1,pair<int,int> &p2){
	if(p1.first==p2.first){
		return p1.second<p2.second;
	}
	return p1.first>p2.first;
}

void graph::top_k(int c,int k){
    pair<int, int> em = {0, 0};
	vector<pair<int, int>> feq(v, em);
	for(int i=0;i<cat[c].size();i++){
		for(auto it=adj[cat[c][i]].begin();it!=adj[cat[c][i]].end();it++){
			feq[(*it).first].first++;
            feq[(*it).first].second = (*it).first;
		}
	}
	sort(feq.begin(),feq.end(),compare);
    for(int i=0;i<k;i++){
        if(feq[i].first == 0) {
            break;
        }
        cout<<(feq[i].second+1)<<" ";
    }
	cout<<endl;
}

void graph::pairwise_dist(int c1,int c2){
	if(flag){
        dis=vector<vector<float> > (v,vector<float>(v,DBL_MAX1));
	    next=vector<vector<int> > (v,vector<int>(v,-1));
        for(int i=0;i<v;i++){
		    for(auto it=adj[i].begin();it!=adj[i].end();it++){
                int k=(*it).first;
                dis[i][k]=(*it).second;
                next[i][k]=k;
            }
        }
		for(int k=0;k<v;k++){
			for(int i=0;i<v;i++){
				for(int j=0;j<v;j++){
					if(dis[i][j]>(dis[i][k]+dis[k][j])){
						dis[i][j]=dis[i][k]+dis[k][j];
						next[i][j]=next[i][k];
                        flag=false;
					}
		            else if(dis[i][j]==dis[i][k]+dis[k][j] && next[i][k]<next[i][j]){
		                next[i][j]=next[i][k];
                        flag=false;
		            }
				}
			}
		}
	}
	for(int i=0;i<cat[c1].size();i++){
		for(int j=0;j<cat[c2].size();j++){
            int a=cat[c1][i],b=cat[c2][j];    
			cout<<a+1<<" "<<b+1<<"\t";
            if(dis[a][b]==DBL_MAX1){
                cout<<"-1"<<endl;
            }
            else{
                cout<<a+1<<" ";
				while(a!=b){
					a=next[a][b];
                    cout<<a+1<<" ";
				}
				cout<<endl;
            }
		}
	}
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed;
	int n,l;
	cin>>n>>l;
	graph g1(n);
	for(int i=0;i<n;i++){
		int x;
		cin>>x;
		g1.cat[x].push_back(i);	
	}
	for(int i=0;i<l;i++){
		int x,y;
        float wt;
		cin>>x>>y>>wt;
		g1.addedge(x-1,y-1,wt);
	}
	string s;
	while(cin>>s){
		if(s=="sssp"){
			int x;
			cin>>x;
			g1.min_time(x-1);
		}
		else if(s=="apsp"){
			int x,y;
			cin>>x>>y;
			g1.pairwise_dist(x,y);
		}
		else if(s=="update"){
			int x;
            float y;
			cin>>x>>y;
			g1.update_network(x-1,y);
		}
		else{
			int x,y;
			cin>>x>>y;
			g1.top_k(x,y);
		}
	}
	return 0;
}
