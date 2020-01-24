#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;

/*class ArraySearch{                                          //ArraySearch class
	private:
		vector<int> vec;
	public:
		int BinarySearch(int x,int start,int end);
		void LinearSearch(int x,int start,int end);
		ArraySearch(vector<int> v){                        //as vec is private
			vec=v;
		}
};*/

int BinarySearch(vector<int> vec,int x,int start,int end){    //BinarySearch meathod
	bool flag;
    int index=-1;                                           //index is the highest position of x in the vec
	int s=start,e=end-1;
	while(s<=e){
		int m=(s+e)/2;
		if(vec[m]==x){
			index=m;
			s=m+1;
		}
		if(vec[m]<x){
			s=m+1;
		}
		else if(vec[m]>x){
			e=m-1;
		}
	}
	if(index==-1){                                          //x is not found so returning lower bound
		return e;
	}
	else{
		return index;                                       //x is found so returning highest position of x
	}
}

int LinearSearch(vector<int> vec,int x,int start,int end){   //LinearSearch meathod   
	bool flag;
	int index;                                              //index is the highest position of x in the vec
	/*if(vec[0]>x){                                           //lowerbound doesnt exist
		index=-1;
		flag=false;
	}*/
	//else{                                                                    
		//flag=true;
		for(int i=end-1;i>=start;i--){
			if(vec[i]==x){
				index=i;
				break;
			}
			if(vec[i]<x){
				index=i;
				break;
			}
		}
	return index;
}

/*class Client{                                              //Client class
	private:
		vector<int> vec;
	public:
		void lower_bound(int x,int start,int end);
		void upper_bound(int x,int start,int end);
		Client(vector<int> v){                            //as vec is private
			vec=v;
		}
};

void Client:: lower_bound(int x,int start,int end){       //lower_bound meathod
	bool flag;                                            //it is same output as BinarySearch
	ArraySearch q(vec);
	cout<<q.BinarySearch(x,start,end)<<endl;
}

void Client:: upper_bound(int x,int start,int end){       //upper_bound meathod
	bool flag;                                            //it is the next index to return value from BinarySearch 
	ArraySearch q(vec);
	cout<<q.BinarySearch(x,start,end)+1<<endl;;
}*/

int main(){
	ifstream file("input06.txt");
	ofstream out1("out1.txt",ios:: app);
	ofstream out2("out2.txt",ios :: app);
	int n,k,b;
	file>>n>>k;
	b=n;
	vector<int> v;
	while(n--){                                          
		int x;
		file>>x;
		v.push_back(x);
	}
	double max1=0.0,max2=0.0,t;
	while(k--){
		int x;
		file>>x;
		clock_t end,start;
		start=clock();
		BinarySearch(v,x,0,n);
		end=clock();
		end-=start;
		t=100.0*(double)(end)/CLOCKS_PER_SEC;
		if(max1<t){
			max1=t;
		}
		//cout<<t<<endl;
		start=clock();
		LinearSearch(v,x,0,n);
		end=clock();
		end-=start;
		t=100.0*(double)(end)/CLOCKS_PER_SEC;
		if(max2<t){
			max2=t;
		}
		//cout<<t<<endl;
	}
	out1<<(log(b)/log(10))<<" "<<max1<<endl;
	out2<<(log(b)/log(10))<<" "<<max2<<endl;
	/*ArraySearch a(v);                                   //a is ArraySearch object, b is Client object
	Client b(v);                                           
	int i=4;
	while(i--){
		string str;
		int x,s,e;
		cin>>str>>x>>s>>e;
		if(str=="BS"){
			if(v[s]<=x){
				cout<<a.BinarySearch(x,s,e)<<endl;
			}
			else{                                       //no lower bound
				cout<<-1<<endl;
			}
		}
		if(str=="LS"){
			if(v[s]<x){
				a.LinearSearch(x,s,e);
			}
			else{                                      //no lower bound
				cout<<-1<<endl;
			}
		}
		if(str=="LB"){
			if(v[s]<=x){
				b.lower_bound(x,s,e);
			}
			else{                                      //no lower bound
				cout<<-1<<endl;
			}
		}
		if(str=="UB"){
			if(v[e-1]>x){
				b.upper_bound(x,s,e);
			}
			else{                                     //no upper bound
				cout<<-1<<endl;
			}
		}
	}*/
	return 0;
}
