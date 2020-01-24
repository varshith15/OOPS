#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int BinarySearch(vector<int> vec,int x,int start,int end){      //function for binary search
	int index=-1,z;
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
	if(index==-1){
		return e;
	}
	else{
		return index;
	}
}

int lower_bound(vector<int> vec,int x,int start,int end){       //function for finding lower bound
	return BinarySearch(vec,x,start,end);
}

int upper_boundd(vector<int> vec,int x,int start,int end){      //function for finding upper bound
	return BinarySearch(vec,x,start,end)+1;
}

/*class Matrix{                                                   //Matrix class
	public:
		vector<vector<int> > mat;
};

class row_sorted_array: public Matrix{
    public:
        int n,m;                                                //n-no.of rows,m-no.of columns
	    void find_median();
        row_sorted_array(vector<vector<int> > v){
            mat=v;
        }
};*/

void find_median(vector<vector<int> >mat,int n,int m){                          //find_median meathod
    long int min=mat[0][0],max=mat[0][m-1];                     //min is minimum in mat,max is maximum
    for(int i=0;i<n;i++){
        if(mat[i][0]<min){
            min=mat[i][0];
        }
        if(mat[i][m-1]>max){
            max=mat[i][m-1];
        }
    }
    long int e=(n*m+1)/2;                                       //e is the position of median 
    while(min<=max){
        long int mid=min+(max-min)/2;
        long int c=0;
        for(int i=0;i<n;i++){
            vector<int> q=mat[i];
            c+=upper_boundd(q,mid,0,m);                         //c is the number of elements before mid if all elements are sorted
        }
        if(c<e){
            min=mid+1;
        }
        else{
            max=mid-1;
        }
    }
    //cout<<min;
}

int main() {
	ifstream file("input10.txt");
	ofstream out("q3median1.txt",ios::app);
    int r,c;
    file>>r>>c;
    vector<vector<int> > v;
    for(int i=0;i<r;i++){                                     //matrix input
        vector<int> q;
        for(int j=0;j<c;j++){
            int x;
            file>>x;
            q.push_back(x);
        }
        v.push_back(q);
    }
    //row_sorted_array a(v);                                    //a is row_sorted_array object
    //a.n=r;a.m=c;
    clock_t start,end;
    double t=0.0;
    start=clock();
    find_median(v,r,c);
    end=clock();
    end-=start;
    t=100.0*end/CLOCKS_PER_SEC;
    out<<log(r)/log(10)<<" "<<t<<endl;
    return 0;
}

