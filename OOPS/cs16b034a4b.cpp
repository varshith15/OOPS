#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	vector<pair<string,int> > v;
	for(int i=0;i<n;i++){
		string s;
		cin>>s;
		int x,y;
		char c;
		cin>>x>>c>>y;
		x=x*100+y;
		pair<string,int> p;
		p.first=s;
		p.second=x;
		v.push_back(p);
	}
	for(int i=0;i<m;i++){
		string s;
		cin>>s;
		int x,y;
		char c;
		cin>>x>>c>>y;
		x=x*100+y;
		pair<string,int> p;
		p.first=s;
		p.second=x;
		int j=0;
		for(j=0;j<n+i;j++){
			if(v[j].first<s){
				int x=v[j].second;
				cout<<v[j].first<<" ";
				cout.width(2);
				cout.fill('0');
				cout<<x/100<<':';
				cout.width(2);
				cout.fill('0');
				cout<<x-(x/100)*100<<endl;
			}
			else if(v[j].first>s){
				v.insert(v.begin()+j,make_pair(s,x));
				break;
			}
			else{
				if(x<v[j].second){
					v.insert(v.begin()+j,make_pair(s,x));
					break;
				}
			}
		}
		if(j==n+i){
			v.push_back(make_pair(s,x));
		}
		for(int k=j;k<=n+i;k++){
			int x=v[k].second;
				cout<<v[k].first<<" ";
				cout.width(2);
				cout.fill('0');
				cout<<x/100<<':';
				cout.width(2);
				cout.fill('0');
				cout<<x-(x/100)*100<<endl;
				cout<<"flag"<<endl;
		}
		cout<<endl;
	}
	
	return 0;
}
