#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
class shape{								//base class
	public:
	float area();
};
class rectangle: public shape{				//rectangle class
	private:
	int a,b,c,d;						
	public:
	rectangle(int a1,int b1,int c1,int d1){	
		a=a1;b=b1;c=c1;d=d1;
	}	
	void area(){							//function overiding
		cout<<((c-a)*(b-d));
	}
	void operator+(rectangle rect){			
		int a1,b1,c1,d1;
		a1=rect.a;
		b1=rect.b;
		c1=rect.c;
		d1=rect.d;
		if((a>c1 || a1>c)||(b<d1 || b1<d)){
			cout<<-1<<endl;
		}
		else{
			int a2,b2,c2,d2;
			a2=max(a,a1);
			b2=min(b,b1);
			c2=min(c,c1);
			d2=max(d,d1);
			//cout<<a2<<" "<<b2<<" "<<c2<<" "<<d2<<endl;
			if(a2==c2){
				if(b2==d2){
					cout<<a2<<" "<<b2<<" "<<0<<endl;
				}
				else{
					cout<<a2<<" "<<max(b2,d2)<<" "<<c2<<" "<<min(d2,b2)<<" "<<0<<endl;
				}
			}
			else{
				if(b2==d2){
					cout<<min(a2,c2)<<" "<<b2<<" "<<max(c2,a2)<<" "<<d2<<" "<<0<<endl;
				}
				else{
					cout<<a2<<" "<<b2<<" "<<c2<<" "<<d2<<" "<<(int)abs((c2-a2)*(b2-d2))<<endl;
				}
			}
			
		}
	}
};
class circle: public shape{					//circle class
	private:
	int x,y,r;	
	public:
	circle(int x1,int y1,int r1){			
		x=x1;y=y1;r=r1;
 	}
	void area(){							//function overiding
		//cout<<3.14*(r*r)<<" ";
		printf("%.2f ",(int)(100*3.14*r*r)/100.0);
	}
	void operator+(circle cir){
		int x1,y1,r1;
		x1=cir.x;
		y1=cir.y;
		r1=cir.r;
		double k;
		k=pow((double)(x1-x),2.0);
		k+=pow((double)(y1-y),2.0);
		double dist=sqrt(k);
		//cout<<dist<<" "<<r+r1<<endl;
		if((r+r1)<dist){
			cout<<-1<<endl;
		}
		else{
			if((r+r1)==dist){
				printf("%.2f %.2f ", (int)(100*((x*r1)+(x1*r))/(r+r1))/100.0, (int)(100*((y*r1)+(y1*r))/(r+r1))/100.0);
				//cout<<1.0*((x*r1)+(x1*r))/(r+r1)<<" "<<((y*r1)+(y1*r))*1.0/(r+r1)<<" ";
			}
			else{
				if((x==x1)&&(y==y1)){
					cout<<0<<" ";
				}
				else{
					if(dist<abs(r-r1)){
						cout<<0<<" ";
					}
					else{
						double k=pow(r,2.0)-pow(r1,2.0);
						double ratio=(k+pow(dist,2.0))/(double)(-k+pow(dist,2.0));
						double x2=(x+(x1)*ratio)/(double)(1.0+ratio);
						//cout<<x2<<endl;
						double y2,y3;
						y2=y3=sqrt(pow(r,2.0)-pow(x-x2,2.0));
						y2=y-y2;
						y3=y+y3;
						double x3=x2;
						if(y2!=y3){
							printf("%.2f %.2f %.2f %.2f ",(int)(100*x2)/100.0,(int)(100*y2)/100.0,(int)(100*x3)/100.0,(int)(100*y3)/100.0);
							//cout<<x2<<" "<<y2<<" "<<x3<<" "<<y3<<" ";
						}
						else{
							printf("%.2f %.2f ",(int)(100*x2)/100.0,(int)(100*y2)/100.0);
							//cout<<x2<<" "<<y2<<" ";
						}
					}
				}
			}
		}
	}
};
int main(){
	//rectangle rect(1,2,3,4);
	int t;
	cin>>t;
	while(t--){
		char ch;
		cin>>ch;
		int a,b,c,d,x,y,r;
		if(ch=='R'){
			cin>>a>>b>>c>>d;
			rectangle rect1(a,b,c,d);
			cin>>a>>b>>c>>d;
			rectangle rect2(a,b,c,d);
			rect1+rect2;
		}
		else if(ch=='C'){
			cin>>x>>y>>r;
			circle cir1(x,y,r);
			cin>>x>>y>>r;
			circle cir2(x,y,r);
			cir1+cir2;
			cir1.area();
			cir2.area();
			cout<<endl;
		}
		/*switch(ch){
			case 'R':
				
				break;
			case 'S':
				
				break;
		}*/
	}
	return 0;
}


