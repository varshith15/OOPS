#include <bits/stdc++.h>
using namespace std;

class graph{                                                //graph class
	private:
		int v;                                             //no.of vertices
		list<int> *adj;                                    //adjacency list
    public:
		graph(int v);                                      //constructor
		void add_edge(int x,int y);                        //fuction for adding edge
		void island();                                     //fuction for finding no.of islands
		void dfs(int a,int vis[]);                         //dfs fucntion
		void cycle();                                      //fuction for finding if cycle exists
		int dfs1(int a,vector<int> &vis,int parent);       //dfs fuction
		void big(int k);                                   //fuction for printing k levels in biggest island
		void small();                                      //for finding time spaces in smallest island
		void dfs2(int s,int vi[],vector<pair<int,pair<int,int> > > &p,int *t);
        int get_v();                                        
        void put_v(int a);
};

int bi=0,co=0;                                              //bi- biggest id of the island,co- no.of cities in the island
int sm=9999999;                                             //sm- smallest id of the island 

int graph::get_v(){
    return v;
}

void graph::put_v(int a){
    v=a;
}

graph:: graph(int v){
	put_v(v);
	adj= new list<int>[v];
}

void graph::add_edge(int v,int w){
	adj[v].push_back(w);
	adj[w].push_back(v);
}

void graph::island(){
	int vis[v]={0};
	int count=0;
	for(int i=0;i<v;i++){
		if(vis[i]==0){
			dfs(i,vis);
			count++;
		}
	}
	cout<<count<<" ";
}

void graph::dfs(int a,int vis[]){                               //dfs using stack
    stack<int> s;
    s.push(a);
    while(!s.empty()){
        a=s.top();
        s.pop();
        if(!vis[a]){
            vis[a]=1;
            if(a>bi){
                bi=a;
            }
            if(a<sm){
                sm=a;
            }
            co++;
        }
        for(auto i=adj[a].begin();i!=adj[a].end();i++){
            if(!vis[*i]){
                s.push(*i);
            }
        }
    }
}

int graph::dfs1(int a,vector<int> &vis,int parent){                //dfs using recursion
	vis[a]=1;
	list<int>:: iterator it;
	for(it=adj[a].begin();it!=adj[a].end();it++){
		if(!vis[*it]){
			if(dfs1(*it,vis,a)){
				return 1;
			}
		}
		else if(*it!=parent){
			return 1;
		}
	}
	return 0;
}

void graph::cycle(){
	vector<int> vis(v);
    for(int i=0;i<v;i++){
        vis[i]=0;
    }
	for(int i=0;i<v;i++){
		if(!vis[i]){
			if(dfs1(i,vis,-1)){
				cout<<"YES"<<endl;
				return;
			}
		}
	}
	cout<<"NO"<<endl;
} 

void graph:: big(int k){
	int vis[v]={0};                                               //ent-entering id,size- no .of cities in the islands
    int ent=9999999,size=-1,b=-1;                                 //b-biggest id of the city in the island
	for(int i=0;i<v;i++){
		co=0;
        sm=9999999;
        bi=-1;
        if(vis[i]==0){
            dfs(i,vis);
            if(size<co){
                size=co;
                ent=sm;
                b=bi;
            }
            else if(size==co){
                if(b<bi){
                    ent=sm;
                    b=bi;
                }
            }
		}
	}
    stack<int> s;
    s.push(ent);
    int vi[v]={0};
    vector<int> vec;
    int a,l=1,j=0;
    int sum=0;
    while(!s.empty()){
        a=s.top();
        s.pop();
        l--;
        if(!vi[a]){
            vec.push_back(a);
            vi[a]=1;
        }
        for(auto i=adj[a].begin();i!=adj[a].end();i++){
            if(!vi[*i] && k){
                s.push(*i);
                sum++;
            }
        }
        if(l==0){
            l=sum;
            k--;
            sum=0;
        }
    }
    sort(vec.begin(),vec.end());
    int flag=0;
    for(int i=1;i<vec.size();i++){
        cout<<vec[i]+1<<" ";
        flag=1;
    }
    if(flag==0){
        cout<<-1;
    }
    cout<<endl;
}

void graph:: dfs2(int s,int vi[],vector<pair<int,pair<int,int> > > &p,int *t){ //dfs2 with time stamps using recursion
    vi[s]=1;
    int d1,d2;
    d1=(*t);
    list<int> l=adj[s];
    l.sort();
    int flag=0;
    for(auto i=l.begin();i!=l.end();i++){
        if(!vi[*i]){
            (*t)+=3;
            dfs2(*i,vi,p,t);
            flag=1;
        }
    }
    if(flag==0){
            (*t)+=2;
            d2=(*t);
    }
    else{
            (*t)++;
            d2=(*t);
    }
    p.push_back(make_pair(s,make_pair(d1,d2)));
}

void graph:: small(){
    int vis[v]={0};
    int ent=-1,size=9999999,s=9999999;                  //ent-id of entering id in island, size-no.of cities in the islands
	for(int i=0;i<v;i++){                               //s-smallest id in the island 
		co=0;
        sm=9999999;
        bi=-1;
        if(vis[i]==0){
            dfs(i,vis);
            if(size>co){
                size=co;
                ent=bi;
                s=sm;
            }
            else if(size==co){
                if(sm<s){
                    ent=bi;
                    s=sm;
                }
            }
		}
	}
    int vi[v]={0};
    int t=0;
    int *x=&t;
    vector<pair<int,pair<int,int> > >  p;
    dfs2(ent,vi,p,x);
    sort(p.begin(),p.end());
    for(int i=0;i<p.size();i++){
        cout<<p[i].first+1<<" "<<(p[i].second).first<<" "<<(p[i].second).second<<endl;
    }
}

int main(){
	int n,c,r,k,s;    //n-no.of cities, c-no.of islands, r-no.of roads,k- maximum distance travel in biggest island in the entrance
	cin>>n>>r>>k;     //s-number of cities in the smallest island 
	graph g1(n);
	for(int i=0;i<r;i++){   //adding edges
		int x,y;
		cin>>x>>y;
		g1.add_edge(x-1,y-1);
	}
	g1.island();
	g1.cycle();
    g1.big(k);
    g1.small();
	return 0;
}

