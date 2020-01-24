#include <bits/stdc++.h>
using namespace std;

class package{
	public:
		string name;
		int cost;
	//public:
		/*void inp_p(string s,int x);
		string get_ps();
		int get_pi();*/
		int cum_c;
		//string cum_s;
		int flag;
		int prev;
};

/*void package:: inp_p(string s,int x){
	name=s;
	cost=x;
}

string package::get_ps(){
	return name; 
}

int package:: get_pi(){
	return cost;
}*/

class destination{
	public:
		int t_q;
		vector<package> p;
	//public:
		/*void inp_d(int x);
		void packinp(package x);
		int get_dt();
		vector<package> get_dp();*/
};

/*void destination:: inp_d(int x){
	t_q=x;
}

void destination:: packinp(package x){
	p.push_back(x);
}

int destination:: get_dt(){
	return t_q;
}

vector<package> destination:: get_dp(){
	return p;
}*/ 

int pcost(vector<destination> d){
	int n=d.size();
	vector<package> &pa=d[n-1].p;
	for(int j=0;j<pa.size();j++){
		pa[j].cum_c=pa[j].cost;
		pa[j].flag=1;
	}
	for(int i=n-2;i>=0;i--){
		vector<package> &p2=d[i+1].p;
		vector<package> &p1=d[i].p;
		int count=0;
		if(d[i+1].t_q<d[i].t_q){
			int j=0,q=0;
			while(j<p1.size() && q<p2.size()){
				if(p2[q].flag==1){
					if(p1[j].cost>p2[q].cost){
						p1[j].cum_c=p1[j].cost+p2[q].cum_c;
						p1[j].prev=q;
						p1[j].flag=1;
						j++;
					}
					else{
						p1[j].flag=0;
						count++;
						j++;
					}
				}
				else{
					q++;
				}
			}
			if(count==p1.size()){
				cout<<-1<<endl;
				return 0;
			}
		}
		else if(d[i+1].t_q>d[i].t_q){
			int j=0,q=0;
			while(j<p1.size() && q<p2.size()){
				if(p2[q].flag==1){
					if(p1[j].cost<p2[q].cost){
						p1[j].cum_c=p1[j].cost+p2[q].cum_c;
						p1[j].prev=q;
						p1[j].flag=1;
						j++;
					}
					else{
						q++;
					}
				}
				else{
					q++;
				}
			}
			if(q==p2.size()){
				while(j<p1.size()){
					p1[j].flag=0;
					count++;
					j++;
				}
			}
			if(count==p1.size()){
				cout<<-1<<endl;
				return 0;
			}	
		}
		else{
			int j=0,q=0;
			while(j<p1.size() && q<p2.size()){
				if(p2[q].flag==1){
					p1[j].cum_c=p1[j].cost+p2[q].cum_c;
					p1[j].prev=q;
					p1[j].flag=1;
					j++;
				}
				else{
					q++;
				}
			}
		}
	}
	long int min=10000000000;
	int l=-1;
	vector<package> &pb=d[0].p;
	for(int i=0;i<pb.size();i++){
		if(min>pb[i].cum_c && pb[i].flag==1){
			min=pb[i].cum_c;
			l=i;
		}
	}
	string sq="";
	for(int i=0;i<n;i++){
		sq+=d[i].p[l].name+" ";
		l=d[i].p[l].prev;
	}
	cout<<min<<endl;
	cout<<sq<<endl;	
	return 0;
}

int main(){
	int n;
	cin>>n;
	vector<destination> d(n);
	for(int i=0;i<n;i++){
		int x;
		cin>>x;
		d[i].t_q=x;
	}
	string dummy;
	getline(cin,dummy);
	for(int i=0;i<n;i++){
		string s,str;
		int a;
		getline(cin,s);
		stringstream ss(s);
		while(ss>>str){
			ss>>a;
			package pa;
			pa.name=str;
			pa.cost=a;
			(d[i].p).push_back(pa);
		}
	}
	//int n=d.size();
	/*vector<package> &pa=d[n-1].p;
	for(int j=0;j<pa.size();j++){
		pa[j].cum_c=pa[j].cost;
		pa[j].cum_s=pa[j].name;
		pa[j].flag=1;
	}
	
	for(int i=0;i<d[n-1].p.size();i++){
		cout<<d[n-1].p[i].cum_c<<" ";
	}
	cout<<endl;*/
	pcost(d);
	/*for(int i=0;i<n;i++){
		cout<<d[i].t_q<<endl;
		for(int j=0;j<d[i].p.size();j++){
			cout<<d[i].p[j].cost<<" ";
		}
		cout<<endl;
	}*/
	return 0;
}
