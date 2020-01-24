#include <bits/stdc++.h>
using namespace std;

class TrieNode{
	public:
		TrieNode *child[26];
		int feq;
		int end;
};

TrieNode *newNode(void){
	TrieNode *p = new TrieNode;
	p->end = 0;
	p->feq = 0;
	return p;
}

void insert(TrieNode *root,string valid){
	TrieNode *p = root;
	for(int i=0;i<valid.size();i++){
		int in = valid[i]-'a';
		if(!(p->child[in])){
			p->child[in] = newNode();
		}
		p = p->child[in];
	}
	p->end = 1;
}

void printwords(TrieNode * root,string s){
	if(root->end == 1){
		cout<<s<<" ";
	}
	for(int i=0;i<26;i++){
		if(root->child[i]){
			char c = i+'a';
			string k= s + c;
			printwords(root->child[i],k);
		}
	}
}

void search(TrieNode *root,string check){
	TrieNode *p = root;
	for(int i=0;i<check.size();i++){
		int in = check[i]-'a';
		p = p->child[in];
	}
	if(p->end==1){
		p->feq+=1;
		cout<<check<<" "<<p->feq<<endl;
	}
	else{
		string s = check;
        cout<<check<<" ";
		printwords(p,s);
		cout<<endl;
	}
}

int main(){
	int n,k;
	cin>>n>>k;
	TrieNode *root = newNode();
	for(int i=0;i<n;i++){
        string x;
		cin>>x;
		insert(root,x);
	}
	for(int i=0;i<k;i++){
        string x;
		cin>>x;
		search(root,x);
	}
	return 0;
}
