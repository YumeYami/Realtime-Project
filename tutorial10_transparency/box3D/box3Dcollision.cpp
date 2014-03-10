#include "box3DglobalRule.h"
#include "Cube.cpp"
#include "Sphere.cpp"
#include "Cylinder.cpp"
#include "Plane.cpp"


void checkCollisionSphereCube(Sphere sp1,vector<Cube> cu){

}
void checkCollisionSphereCylinder(Sphere sp1,vector<Cylinder> cy){

}
void checkCollisionSpherePlane(Sphere sp1,vector<Plane> pl){
	for(int j=0;j<pl.size;j+){
			Plane pl1 = pl.at(j);
			vec3 d = sp1.getPos() - pl1.getPos();
			float distance = d.length;
			if(distance<=sp1.getRadius()) {
			
			
			}
	}
}

void checkCollisionSphereSphere(Sphere sp1, vector<Sphere> sp, int i){
	for(int j=i;j<sp.size;j++){
			Sphere sp2 = sp.at(j);
			vec3 d = sp1.getPos() - sp2.getPos();
			float distance = d.length;
			float sumR = sp1.getRadius() + sp2.getRadius();
			if(distance<=sumR) {
			
			
			}
	}
}
void checkCollisionPlaneCube(Plane pl1,vector<Cube> cu){
	float plPos = pl1.getPos()[1];
	for(int j=0;j<cu.size;j++){
		Cube cu1 = cu.at(j);
		if(cu1.getMin()[1]<=plPos) {
			
			
		}
	}
}
void checkCollisionPlaneCylinder(Plane pl1,vector<Cylinder> cy){

}
void checkCollisionPlanePlane(Plane pl1,vector<Plane> pl,int i){
}

void checkCollisionCubeCube(Cube cu1,vector<Cube> cu,int i){
	for(int j=i;j<cu.size;j++){
			Cube cu2 = cu.at(j);
			if(cu1.getMax()[0]>=cu2.getMin[0] && cu1.getMin()[0]>=cu2.getMax[0]
			&& cu1.getMax()[1]>=cu2.getMin[1] && cu1.getMin()[1]>=cu2.getMax[1]
			&& cu1.getMax()[2]>=cu2.getMin[2] && cu1.getMin()[2]>=cu2.getMax[2]) {
			
			
			}
	}
}
void checkCollisionCubeCylinder(Cube cu1,vector<Cylinder> cy){

}
void checkCollisionCylinderCylinder(Cylinder cy1,vector<Cylinder> cy,int i){

}

void checkCollision(vector<Cube> cu, vector<Cylinder> cy, vector<Plane> pl, vector<Sphere> sp){
	for(int i=0;i<sp.size;j++){
		Sphere sp1 = sp.at(i);
		checkCollisionSphereCube(sp1,cu);
		checkCollisionSphereCylinder(sp1,cy);
		checkCollisionSpherePlane(sp1,pl);
		checkCollisionSphereSphere(sp1,sp,i+1);
	}
	for(int i=0;i<pl.size;j++){
		Plane pl1 = pl.at(i);
		checkCollisionPlaneCube(pl1,cu);
		checkCollisionPlaneCylinder(pl1,cy);
		checkCollisionPlanePlane(pl1,pl,i+1);
	}
	for(int i=0;i<cu.size;j++){
		Cube cu1 = cu.at(i);
		checkCollisionCubeCube(cu1,cu,i+1);
		checkCollisionCubeCylinder(cu1,cy);
	}
	for(int i=0;i<cy.size;j++){
		Cylinder cy1 = cy.at(i);
		checkCollisionCylinderCylinder(cy1,cy,i+1);
	}
}



