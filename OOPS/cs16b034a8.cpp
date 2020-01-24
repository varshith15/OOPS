#include <bits/stdc++.h>
using namespace std;
	
class emp{                      //employee class
	private:
		int sup;                  //supervisor id
		int o_i;                  //employee id
		int o_v;                  //employee value
		emp *left;                //left chlid pointer
		emp *right;               //right child pointer
    public:
        int get_sup();              //returns supervisor id
        int get_oi();               //returns employee id 
        int get_ov();               //returns employee value
        emp* getleft();             //returns employee left child
        emp* getright();            //returns employee right child
        void put_oi(int s);         //putting value in o_i
        void put_ov(int s);         //putting value in o_v
        void put_sup(int s);        //putting value in supervisor id
        void put_left(emp *e);      //putting pointer into left
        void put_right(emp *e);     //putting pointer into right
};	

int emp::get_sup(){
    return sup;
}

int emp::get_oi(){
    return o_i;
}

int emp::get_ov(){
    return o_v;
}

emp* emp::getleft(){
    return left;
}

emp* emp::getright(){
    return right;
}

void emp::put_sup(int s){
    sup=s;
}

void emp::put_oi(int s){
    o_i=s;
}

void emp::put_ov(int s){
    o_v=s;
}

void emp::put_left(emp *e){
    left=e;
}

void emp::put_right(emp *e){
    right=e;
}


int level(emp *ceo){                //for finding height
    if(ceo==NULL){
        return 0;
    }
    else{
            int ld=level(((*ceo).getleft()));
            int rd=level(((*ceo).getright()));
        if(ld>rd){
            return ld+1;
        }
        else{
            return rd+1;
        }
    }
}

void printlevel(emp *ceo){        //for printing all the employee ids in level order
    if(ceo==NULL){
        return;
    }
    queue<emp *>q;
    q.push(ceo);
    while(1){
        int count=q.size();
        if(count==0){
            break;
        }
        while(count>0){
            emp *e=q.front();
            cout<<(*e).get_oi()<<" ";
            q.pop();
            if((*e).getleft()!=NULL){
                q.push((*e).getleft());    
            }
            if((*e).getright()!=NULL){
                q.push((*e).getright());    
            }
            count--;
        }
    }
    cout<<endl;
}

void mul(emp *ceo){            //for printing  product of all the ids in the level
    if(ceo==NULL){
        return;
    }
    queue<emp *>q;
    q.push(ceo);
    int l=1;
    while(1){
        int m=1;
        int count=q.size();
        if(count==0){
            break;
        }
        while(count>0){
            emp *e=q.front();
            m*=(*e).get_oi();
            q.pop();
            if((*e).getleft()!=NULL){
                q.push((*e).getleft());    
            }
            if((*e).getright()!=NULL){
                q.push((*e).getright());    
            }
            count--;
        }
        cout<<l<<" "<<m<<" ";
        l++;
    }
    cout<<endl;
}

void hie1(emp *ceo){         //for printing preorder (parent->left->right)
    if(ceo==NULL){
        return;
    }
    stack<emp *> e;
    e.push(ceo);
    while(!e.empty()){
        emp *a=e.top();
        cout<<(*a).get_oi()<<" ";
        e.pop();
        if((*a).getright()!=NULL){
            e.push((*a).getright());
        }
        if((*a).getleft()!=NULL){
            e.push((*a).getleft());
        }
    }
    cout<<endl;
}

void inc(emp *ceo){        //for modifying the o_v with the condition that leftchild+rightchild=parent
    if(ceo==NULL){
        return ;
    }
    emp *x=(*ceo).getleft();
    emp *y=(*ceo).getright();
    inc(x);
    inc(y);
    if(x==NULL && y==NULL){
        return;
    }
    int sum=0;
    if(x!=NULL){
        sum+=(*x).get_ov();
    }
    if(y!=NULL){
        sum+=(*y).get_ov();
    }
    if(sum>=(*ceo).get_ov()){
        (*ceo).put_ov(sum);
    }
    else{
        int l=((*ceo).get_ov())-sum;
        if(x!=NULL){
	    int k=l+(*x).get_ov();
            (*x).put_ov(k);
            inc(x);
        }
        else{
	    int k=l+(*y).get_ov();
            (*y).put_ov(k);
            inc(y);
        }
    }
}


void hie2(emp *ceo){            //for printing the ids in inorder(left->parent->right)
    emp *a=ceo;
    emp *b=NULL;
    stack<emp *> e;
    int flag=0;
    while(!flag){
        if(a!=NULL){
            e.push(a);
            a=(*a).getleft();
        }
        else{
            if(!e.empty()){
                a=e.top();
                e.pop();
                cout<<(*a).get_ov()<<" ";
                a=(*a).getright();
            }
            else{
                flag=1;
            }
        }
    }
    cout<<endl;
}

void max(vector<emp> e){        //for finding the no.of nodes in the max path of the tree
    int max=0;
    for(int i=0;i<e.size();i++){
        int x=level(e[i].getleft())+level(e[i].getright());
        if(max<x+1){
            max=x+1;
        }
    }
    cout<<max<<endl;
}

int main(){
	int n;
	cin>>n;
	vector<int> d(n);              //vector of supervisors ids
	vector<emp> e;                 //vector of employees
	emp *ceo;                      //ceo is the employee with no parent
	for(int i=0;i<n;i++){
		emp a;
		a.put_oi(i);
        a.put_ov(i);
		a.put_left(NULL);
		a.put_right(NULL);
		e.push_back(a);
		cin>>d[i];
	}
	for(int i=0;i<n;i++){
		e[i].put_sup(d[i]);
		if(d[i]!=-1){
			if(e[d[i]].getleft()==NULL){
				e[d[i]].put_left(&e[i]);
			}
			else{
				e[d[i]].put_right(&e[i]);
			}
		}
		else{
			ceo=&e[i];
		}
	}
	cout<<level(ceo)<<endl;
    printlevel(ceo);
    mul(ceo);
    hie1(ceo);
    inc(ceo);
    hie2(ceo);
    max(e);
	return 0;
}

