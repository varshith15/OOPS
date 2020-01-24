#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sstream>
using namespace std;
/*class stack{
    private:
    stack <int> s;
    public:
    int sizeofstack();
    void printstack();
    void getstack(char* str);
    void compare(stack <int> a);
    stack<int> getstack(stack<int> a);
    void input(char* str);
};*/
/*class myqueue{
    private:
    queue<int> q;
    public:
    int sizeofqueue();
    void printqueue();
    void addidtoqueue(int id);
};*/
int sizeofstack(stack <int> s){
    stack <int> a=s;
    int n=0;
    while(!a.empty()){
        a.pop();
        n++;
    }
    return n;
}
void printstack(stack <int> s){
    stack<int> a=s;
    int n=sizeofstack(a);
    int arr[n],i=0;
    while(!a.empty()){
        cout<<a.top()<<" ";
        a.pop();
    }
}
int sizeofqueue(queue<int> q){
    queue<int> a=q;
    int n=0;
    while(!a.empty()){
        a.pop();
        n++;
    }
    return n;
}
void printqueue(queue<int> q){
    queue<int> a=q;
    while(!a.empty()){
        cout<<a.front()<<" ";
        a.pop();
    }
}
int main() {   
    int t;
    cin>>t;
    getchar();
    stack<int> s[t];
    for(int i=0;i<t;i++){
    	stack<int> temp;
    	/*char inp[300];
    	fgets(inp,300,stdin);
    	int n=strlen(inp);
    	if(i!=(t-1)){
    		inp[n-1]='\0';
    	}
    	char q[4];
    	for(int j=0;j<n;j++){
    		int a=0;
    		q[a++]=inp[j++];
    		while((inp[j]!=' ')){
    			q[a++]=inp[j++];
    		}
    		q[a]='\0';
    		temp.push(atoi(q));  		
    	}*/
    	string str;
		getline(cin,str);
		stringstream ss(str);
		int n;
		while(ss>>n){
			temp.push(n);
		}
    	while(!temp.empty()){
    		s[i].push(temp.top());
    		temp.pop();
    	}
    }
    vector<pair<int,int>> vect; 
    for(int i=1;i<t;i++){
    	pair<int,int> p;
    	stack<int> cmp=s[0];
    	int flag=0;
    	while(!flag){
    		if(s[i].top()!=cmp.top()){
    			flag=1;
    			break;
    		}
    		s[i].pop();
    		cmp.pop();
    		if(s[i].empty() || cmp.empty()){
    			flag=1;
    			break;
    		}
    	}
    	p.first=sizeofstack(s[i]);
    	p.second=i;
    	vect.push_back(p);
    }
    sort(vect.begin(),vect.end());
    printstack(s[0]);
    for(int i=0;i<t-1;i++){
   		printstack(s[vect[i].second]);
   	}
    return 0;
}

