#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
bool fun(int i,int j){
	if(abs(i)==abs(j)){
		if(i>0){
			return true;
		}
		else{
			return false;
		}
	}
	return abs(i)>abs(j);
}
class matrix{								//matrix class
	public:
	int mat[100][100];
	int r,c;						
	void operator+(matrix mat1){			//SPC
		int k=min(c,mat1.c);
		for(int i=0;i<r;i++){
			vector<int> v;
			for(int j=0;j<c;j++){
				v.push_back(mat[i][j]);
			}
			for(int j=0;j<mat1.c;j++){
				v.push_back(mat1.mat[i][j]);
			}
			sort(v.begin(),v.end(),fun);
			for(int q=0;q<k;q++){
				cout<<v[q]<<" ";
			}
			cout<<endl;
		}
	}
	void operator&(){						//MSM
		int sum=0;
		int l=2000000000;
		int flag=0;
		for(int i=r-1;i>-1;i--){
			vector<int> v;
			for(int q=0;q<c;q++){
				v.push_back(mat[i][q]);
			}
			vector<int>::iterator low;
			sort(v.begin(),v.end());
			low=lower_bound(v.begin(),v.end(),l);
			if((low-v.begin())!=0){
				sum+=v[low-v.begin()-1];
				l=v[low-v.begin()-1];
			}
			else{
				cout<<"NO"<<endl;
				flag=1;
				break;
			}
		}
		if(flag==0){
			cout<<sum<<endl;
		}
	}
	void operator-(matrix mat1){			//CONV
		int r1=mat1.r;
		int c1=mat1.c;
		int a[r-(r1-1)][c-(c1-1)];
		for(int i=0;i<r-(r1-1);i++){
			for(int j=0;j<c-(c1-1);j++){
				a[i][j]=0;
				for(int q=i;q<i+r1;q++){
					for(int w=j;w<j+c1;w++){
						a[i][j]+=mat[q][w]*(mat1.mat[q-i][w-j]);
					}
				}
			}
		}
		for(int i=0;i<r-(r1-1);i++){
			for(int j=0;j<c-(c1-1);j++){
				cout<<a[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	void operator*(int k){					//ROT
		vector<int> v;
		for(int i=0;i<c;i++){
			v.push_back(mat[0][i]);
		}
		for(int i=1;i<r;i++){
			v.push_back(mat[i][c-1]);
		}
		for(int i=c-2;i>=0;i--){
			v.push_back(mat[r-1][i]);
		}
		for(int i=r-2;i>0;i--){
			v.push_back(mat[i][0]);
		}
		v.insert(v.end(),v.begin(),v.end());
		int l=k%(v.size()/2);
		l=((v.size())/2)-l;
		for(int i=0;i<c;i++){
			mat[0][i]=v[(l++)%(v.size())];
			//cout<<mat[0][i];
		}
		for(int i=1;i<r;i++){
			mat[i][c-1]=v[(l++)%(v.size())];
		}
		for(int i=c-2;i>=0;i--){
			mat[r-1][i]=v[(l++)%(v.size())];
		}
		for(int i=r-2;i>0;i--){
			mat[i][0]=v[(l++)%(v.size())];
		}
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				cout<<mat[i][j]<<" ";
			}
			cout<<endl;
		}
		//cout<<l<<endl;
		/*for(int i=0;i<v.size();i++){
			cout<<v[i]<<" ";
		}*/
	}	
};
int main(){
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		if(s=="MSM"){
			int n,m;
			cin>>n>>m;
			matrix m1;
			m1.r=n;
			m1.c=m;
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){
					cin>>m1.mat[i][j];
				}
			}
			&m1;
		}
		else if(s=="CONV"){
			matrix m1,m2;
			int n1,m11,n2,m21;
			cin>>n1>>m11;
			m1.r=n1;
			m1.c=m11;
			for(int i=0;i<n1;i++){
				for(int j=0;j<m11;j++){
					cin>>m1.mat[i][j];
				}
			}
			cin>>n2>>m21;
			m2.r=n2;
			m2.c=m21;
			for(int i=0;i<n2;i++){
				for(int j=0;j<m21;j++){
					cin>>m2.mat[i][j];
				}
			}
			m1-m2;
		}
		else if(s=="ROT"){
			int n,m,k;
			cin>>n>>m;
			matrix m1;
			m1.r=n;
			m1.c=m;
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){
					cin>>m1.mat[i][j];
				}
			}
			cin>>k;
			m1*k;
		}
		else if(s=="SPC"){
			matrix m1,m2;
			int n1,m11,n2,m21;
			cin>>n1>>m11;
			m1.r=n1;
			m1.c=m11;
			for(int i=0;i<n1;i++){
				for(int j=0;j<m11;j++){
					cin>>m1.mat[i][j];
				}
			}
			cin>>n2>>m21;
			m2.r=n2;
			m2.c=m21;
			for(int i=0;i<n2;i++){
				for(int j=0;j<m21;j++){
					cin>>m2.mat[i][j];
				}
			}
			m1+m2;	
		}
	}
	return 0;
}
