#include <bits/stdc++.h>
#include <iterator>
using namespace std;

class sorting1{
	public:
		bool operator()(const pair<long int,long int> &p1,const pair<long int,long int> &p2){
			if(p1.first==p2.first){
				return(p1.second>p2.second);
			}
				return(p1.first>p2.first);
		}
};

class sorting{
	public:
		bool operator()(const pair<string,long int> &p1,const pair<string,long int> &p2){
			if(p1.second==p2.second){
				return(p1.first<p2.first);
			}
			return(p1.second>p2.second);
		}
};
class spec{
	public:
	long int id;
	map<string,long int> feq;
};
int main(){
	long int n,k,m;
	cin>>n>>k;
	map<string,long int> ff;
	vector<spec> v;
	for(long int i=0;i<n;i++){
		long int x;
		cin>>x;
		vector<spec>::iterator it;
		for(it=v.begin();it<v.end();it++){
			if(it->id==x){
				break;
			}
		}
		if(it==v.end()){
			spec a;
			a.id=x;
			string s;
			getline(cin,s);
			long int q=s.size();
			for(long int j=0;j<q;j++){
				string w;
				int flag=0;
				while(j<q && (isalpha(s[j]) || isdigit(s[j]))){
					char c=s[j];
					if(isupper(c)){
						s[j]=tolower(c);
					}
					w+=s[j];
					j++;
					flag=1;
				}
				if(flag==1){
					w+='\0';
					if(a.feq.find(w)!=a.feq.end()){
						a.feq[w]++;
					}
					else{
						a.feq.insert(pair<string,long int> (w,1));
					}
					if(ff.find(w)!=ff.end()){
						ff[w]++;
					}
					else{
						ff.insert(pair<string,long int> (w,1));
					}
				}
			}
			v.push_back(a);
		}
		else{
			it->id=x;
			string s;
			getline(cin,s);
			long int q=s.size();
			for(long int j=0;j<q;j++){
				string w;
				int flag=0;
				while(j<q && (isalpha(s[j]) || isdigit(s[j]))){
					char c=s[j];
					if(isupper(c)){
						s[j]=tolower(c);
					}
					w+=s[j];
					j++;
					flag=1;
				}
				if(flag==1){
					w+='\0';
					if((it->feq).find(w)!=(it->feq).end()){
						(it->feq)[w]++;
					}
					else{
						(it->feq).insert(pair<string,long int> (w,1));
					}
					if(ff.find(w)!=ff.end()){
						ff[w]++;
					}
					else{
						ff.insert(pair<string,long int> (w,1));
					}
				}
			}
		}
	}
	map<string,long int>::iterator it;
	vector<pair<string,long int> > vec;	
	for(it=ff.begin();it!=ff.end();it++){
		string t=it->first;
		long int p=it->second;
		vec.push_back(make_pair(t,p));
	}
	sort(vec.begin(),vec.end(),sorting());
	for(int i=0;i<k;i++){
		vector<pair<long int,long int> > vec1;
		string t=vec[i].first;
		vector<spec>::iterator it;
		//for(int j=0;j<v.end();j++){
		for(it=v.begin();it<v.end();it++){
			//cout<<it->id<<endl;
			map<string,long int>::iterator it1;
			for(it1=(it->feq).begin();it1!=(it->feq).end();it1++){
				if(it1->first==t){
					vec1.push_back(make_pair(it1->second,it->id));
					//cout<<it1->second<<" "<<it->id<<endl;
				}
			}
		}
		sort(vec1.begin(),vec1.end(),sorting1());
		cout<<t<<' ';
		long int p=0;
		while(vec1[p].first==vec1[0].first && p<vec1.size()){
			cout<<vec1[p].second<<' ';
			p++;
		}
        
		cout<<'\n';
	}
	return 0;
}

