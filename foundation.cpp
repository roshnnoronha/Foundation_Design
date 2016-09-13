#include "foundation.h"
using namespace std;
namespace foundation{
	foundation::foundation(){}
	foundation::foundation(string csValues){
		cout<< csValues.size()<<endl;
		int ctr;
		string s;
		for(int i=0;i<csValues.size();i++){			
			if(csValues[i]==','){
				cout<<s<<endl;
				ctr++;
				s="";
			}else{
				s=s+csValues[i];
			}
		}
			
		
	}
}
