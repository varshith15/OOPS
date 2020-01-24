#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
/*class Matrix{                               //matrix class
	public:
		vector<vector<int> > mat;           //mat is a matrix
};*/
/*class sorted_array: public Matrix{          //sorted_array class inherited from Matrix class
    public:
    int n,m;                                //n-no.of rows,m-no.of columns
    sorted_array(vector<vector<int> > v){
        mat=v;
    }
	pair<int,int> sorted_search(int x);
};*/
pair<int,int> sorted_search(vector<vector<int> > mat,int x,int n,int m){   //sorted_search meathod
    int i=0,j=m-1;
    bool flag=false;
    pair<int,int> p;
    while(i<n && j>=0){
        if(mat[i][j]==x){
            flag=true;
            break;
        }
        else if(mat[i][j]>x){
            j--;
        }
        else if(mat[i][j]<x){
            i++;
        }
    }
    if(flag==true){
        p.first=i;
        p.second=j;
        return p;
    }
    else{                                   //element doesnt exist
        p.first=-1;
        p.second=-1;
        return p;
    }
}

int main() {
	ifstream file("input01.txt");
	ofstream out("q2search.txt",ios::app);
	clock_t start,end;
	double max=0.0,t;
    int r,c,k;                                //r-rows,c-column
    file>>r>>c>>k;
    vector<vector<int> > v;
    for(int i=0;i<r;i++){
        vector<int> q;
        for(int j=0;j<c;j++){
            int x;
            file>>x;
            q.push_back(x);
        }
        v.push_back(q);
    }
    //sorted_array a(v);                     //a is sorted_array object
	for(int i=0;i<k;i++){
    int x;
    file>>x;
    start=clock();
    sorted_search(v,x,r,c);
    end=clock();
    end-=start;
    t=100.0*(end)/CLOCKS_PER_SEC;
    if(max<t){
    	max=t;
    }
    }
    out<<log(r+c)/log(10)<<" "<<max<<endl;
    //cout<<p.first<<" "<<p.second<<" "<<endl;
    return 0;
}

