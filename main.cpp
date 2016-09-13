#include "foundation.h"
#include <iostream>
#include <stdlib>
using namespace std;
int foundation::foundation::a=1;
int main(){
	system("cls");
	cout<<"Foundation Design Module"<<endl;
	cout<<"========================"<<endl;
	
	foundation::foundation::a=2;	
	cout<<foundation::foundation::a<<endl;
	foundation::foundation F("123,4,34,wqerwe");
	return 0;
}