#include "load.h"
namespace foundation{
load::load(double fx,double fy,double fz,double mx,double my,double mz):FX(fx),FY(fy),FZ(fz),MX(mx),MY(my),MZ(mz)
{}
load::load()
{FX=0;FY=0;FZ=0;MX=0;MY=0;MZ=0;}
}
/*
void main(){
	foundation::load l(1,2,3,4,5,6);
}*/