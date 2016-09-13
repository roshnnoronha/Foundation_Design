/*
Started			:17 june 2016
Last modified 	:17 june 2016
Notes			:
	Axis assumed	
					^Y
					|
				 B	|
				 	------->X
					   L
*/
#include <iostream>
namespace foundation{
class linearBearingPressure{
public:
	linearBearingPressure(double length, double width, double vertLoad,double momentX, double momentY);
	double getMaximumPressure();
	double calculateVolume(double m, double n);
	double calculateVolume1(double p, double a, double b);
	double calculateCGx(double m, double n);
	double calculateCGx1(double p,double a, double b);
private:
	double L,B; 		//foundation dimensions
	double P,Mx,My; 	//foundation loads
	double Pmax;
	double Pmax_int;
	double calculatePmax_int();

};
linearBearingPressure::linearBearingPressure(double length, double width, double vertLoad,double momentX, double momentY):
L(length),B(width),P(vertLoad),Mx(momentX),My(momentY){
	calculatePmax_int();
}
double linearBearingPressure::getMaximumPressure(){return Pmax;}
double linearBearingPressure::calculatePmax_int(){
	double A, Zx, Zy;
	A=L*B;
	Zx= L*B*B/6;
	Zy= B*L*L/6;
	return P/A+Mx/Zx+My/Zy;
}
double linearBearingPressure::calculateVolume(double m , double n){
	double A_,B_,C_,D_,V1,V2,D1,D2;
	A_ = P*B*n;
	B_ = P*L*m;
	C_ = -L*B*(-n-m+m*n);
	D_ = -P*L*B*(-n-m+m*n);
	V1 = L*B*(1-m)/(2*C_)*(2*D_-B_*B-A_*L*(1-m));
	D1=(D_-A_*L*(1-m));
	D2=D_-A_*L;
	V2 = 1/(6*A_*C_*B_) *  (D1*D1*D1-D2*D2*D2);
	return V1+V2;
}
double linearBearingPressure::calculateVolume1(double p, double a, double b){
	double v;
	v=p*(B*(L-a)/2+ a*a*(b*b+3*B*B-3*B*b)/(6*(L*b+B*a-a*b)));
	return v;
}
double linearBearingPressure::calculateCGx(double m, double n){
	double A_,B_,C_,D_,V,C1,C2,r1,r2,k,r1_2,r2_2;
	A_ = P*B*n;
	B_ = P*L*m;
	C_ = -L*B*(-n-m+m*n);
	D_ = -P*L*B*(-n-m+m*n);
	V=calculateVolume(m,n);
	k=(1-m)*L;
	C1=B/(12*C_)*k*k*(6*D_-4*A_*k-3*B_*B);
	r1=D_-A_*L;
	r2=D_-A_*k;
	r2_2=r2*r2;
	r1_2=r1*r1;
	C2=1/(12*A_*A_*B_*C_)*(4*D_*(r2_2*r2-r1_2*r1)-3*(r2_2*r2_2-r1_2*r1_2));
	return (C1+C2)/V;
}
double linearBearingPressure::calculateCGx1(double p, double a, double b){
	double CGx,v;
	CGx= (p*B*(L-a)*(L-a)*(2*L*b+3*B*a-2*a*b)+p*a*a*b*(4*L*b+4*B*a-7*a*b))/(12*(L*b+B*a-a*b));
	v=calculateVolume1(p,a,b);
	CGx /= v;
	return CGx;
}
}

void main(){
	foundation::linearBearingPressure a(3,3,4,20,2);
	std::cout<< "Initial Max Pressure:" << a.getMaximumPressure() << std::endl;
	std::cout<< "Volume:" << a.calculateVolume(0.167, 0.333)<<std::endl;
	std::cout<< "Volume1:" << a.calculateVolume1(4.0, 0.5, 1.0)<<std::endl;
	std::cout<< "CGx:" << 3-a.calculateCGx(0.167, 0.333)<<std::endl;
	std::cout<< "CGx1:" << 3-a.calculateCGx1(4.0,0.5, 1.0)<<std::endl;
	std::cout<<"Target is 1.94"<<std::endl;
}	