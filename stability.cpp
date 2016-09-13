/*Defined in foundation class:
A,B,t,depth,gammac,gammas,ped
*/
#include <vector>
Using namespace std;
namespace foundation{
double foudation::stability(){
	vector <double> OM(ped[0].load.size()), RM(ped[0].load.size());
	double OM_min;
	//calculate restoring moment due to soil and self-weight
	double wf,ws;
	vector <double> wp(ped.size());
	wf=A*B*t*gammac;	//foundation weight
	mom_wf1=wf*A/2; mom_wf2= mom_wf1;	//moment about line X=0 and X=A
	mom_wf3=wf*B/2; mom_wf4= mom_wf3;	//moment about line Z=0 and Z=B
	ws=A*B*(depth-t) * gammas;	//soil weigth
	mom_ws1=ws*A/2; mom_ws2=mom_ws1;
	mom_ws3=ws*B/2; mom_ws4= mom_ws3;
	for(int i=0;i<ped.size();i++){
		double Aped;
		Aped= ped[i].LX*ped[i].LZ;
		ws -= Aped*gammas;	//subtract pedestal area from soil weigth
		mom_ws1-=ws*ped[i].x;
		mom_ws2-=ws*(A-ped[i].x);
		mom_ws3-=ws*ped[i].z;
		mom_ws4-=ws*(B-ped[i].z);
		wp += Aped*(depth-t+h)*gammac;	//pedestal weigth
		mom_wp1 += wp*ped[i].x;
		mom_wp2 += wp*(A-ped[i].x);
		mom_wp3 += wp*ped[i].z;
		mom_wp4 += wp*(B-ped[i].z);
	}
	for(int i=0;i<ped.load.size();i++){
		double OM1,OM2,OM3,OM4,RM1,RM2,RM3,RM4;
		RM1=mom_wf1+mom_ws1+mom_wp1;
		RM2=mom_wf2+mom_ws2+mom_wp2;
		RM3=mom_wf3+mom_ws3+mom_wp3;
		RM4=mom_wf4+mom_ws4+mom_wp4;
		RF=wf+ws+wp;
		for(int j=0;j<ped.size();j++){
			//-ve vertical force causes overturning 
			if(ped[j].load.FY<0){ 
				OM1 -= ped[j].load.FY*ped[j].x; 
				OM2 -= ped[j].load.FY*(A-ped[j].x);
				OM3 -= ped[j].load.FY*ped[j].z;
				OM4 -= ped[j].load.FY*(B-ped[j].z);
			}
			else {
				RM1 += ped[j].load.FY*ped[j].x;
				RM2 += ped[j].load.FY*(A-ped[j].x);
				RM3 += ped[j].load.FY*ped[j].z;
				RM4 += ped[j].load.FY*(B-ped[j].z);
			}
			//-ve horizontal force causes overturning about X=0 and restoring about X=A
			if(ped[j].load.FX<0) {
				OM1 -= ped[j].load.FX*depth; 
				RM2 -= ped[j].load.FX*depth; 
			}
			else {
				RM1 += ped[j].load.FX*depth;
				OM2 += ped[j].load.FX*depth;
			}
			//-ve horizontal force cause overturing about Z=0 and restoring about Z=B
			if(ped[j].load.FZ<0) {
				OM3 -= ped[j].load.FZ*depth; 
				RM4 -= ped[j].load.FZ*depth; 
			}
			else {
				RM3 += ped[j].load.FZ*depth;
				OM4 += ped[j].load.FZ*depth;
			}
			//Sliding force along X
			SFx += ped[j].load.FX;
			//Sliding force along Z
			SFz += ped[j].load.FZ;
			//Restoring force for sliding
			RF += ped[j].load.FY;
		}	
		FOS_x0[i]=RM1/OM1;
		FOS_xA[i]=RM2/OM2;
		FOS_z0[i]=RM3/OM3;
		FOS_zB[i]=RM4/OM4;
		SF= sqrt(SFx^2+SFz^2); //resultant sliding force
		FOS_s[i]=RF*mu/SF;
	}
}
}
