#include <bits/stdc++.h>
using namespace std;

int main(){
	int p;
	cin>>p;
	vector<pair<string,double> > v;
	vector<string> v1;
	while(p--){
		string s;
		double x;
		cin>>s>>x;
		v.push_back(make_pair(s,x));
	}
	int q;
	cin>>q;
	while(q--){
		string s;
		cin>>s;
		if(s=="INSERT"){
			string q;
			double x;
			cin>>q>>x;
			vector<pair<string,double> >:: iterator it;
			vector<string>:: iterator it1;
			int r;
			for(r=0;r<v1.size();r++){
				if(v1[r]==q){
					break;
				}
			}
			if(r!=v1.size()){
				cout<<"ALREADY ADMITTED"<<endl;
			}
			else{
				for(it=v.begin();it<v.end();it++){
					if(it->first==q){
						break;
					}
				}
				pair<string,double> p;
				if(it<v.end()){
					//cout<<"ALREADY ADMITTED"<<endl;
					p.first=it->first;
					double w=it->second;
					w+=x;
					w=w/2.0;
					p.second=w;
					v.erase(it);
				}
				else{
					p.first=q;
					p.second=x;
				}
				//sort
				int i;
				for(i=0;i<v.size();i++){
					if(p.second>v[i].second){
						v.insert(v.begin()+i,p);
						break;
					}
					else if(p.second==v[i].second){
						string s1=p.first;
						string s2=v[i].first;
						int sum1=char(s1[0])+char(s1[1])+char(s1[2])+char(s1[3])+char(s1[4])+char(s1[5])+char(s1[6]);
						int sum2=char(s1[0])+char(s1[1])+char(s1[2])+char(s1[3])+char(s1[4])+char(s1[5])+char(s1[6]);
						if(sum1<sum2){
							v.insert(v.begin()+i,p);
							break;
						}
						else if(sum1==sum2){
							if(p.first<v[i].first){
								v.insert(v.begin()+i,p);
								break;
							}
						}
					}	
				}
				if(i==v.size()){
					v.insert(v.begin(),p);	
				}
			}
		}
		else if(s=="IS_ADMIT"){
			int n,m;
			cin>>m>>n;
			if(v.size()<10){
				cout<<"NO"<<endl;
			}
			else{
				int count=v.size();
				double h=v[0].second;
				int check=floor((m*count)/100); 
				double x=(n*h*1.0)/100.0;
				if(v[check-1].second<x){
					cout<<"NO"<<endl;
				}
				else{
					cout<<"YES"<<endl;
					//poping 10% of count
					int erase=count/10;
					for(int i=0;i<erase;i++){
						v1.push_back(v[i].first);
						cout<<v[i].first<<" ";
						cout<<setiosflags(ios::fixed)<<setprecision(3)<<v[i].second<<endl;	
						v.erase(v.begin());
					}
				}
			}
		}
		else{
			string z;
			getline(cin,z);
			int s,e;
			
			if(z==""){
				//cout<<"ffs"<<endl;
				for(int i=0;i<v.size();i++){
					cout<<v[i].first<<" ";
					cout<<setiosflags(ios::fixed)<<setprecision(3)<<v[i].second<<endl;
				}
			}
			else{
				stringstream ss(z);
				ss>>s>>e;
				//cout<<"ffs1"<<endl;
				s--;
				e--;
				for(int i=s;i<=e;i++){
					cout<<v[i].first<<" ";
					cout<<setiosflags(ios::fixed)<<setprecision(3)<<v[i].second<<endl;
				}
			}
		}
	}
	return 0;
}
