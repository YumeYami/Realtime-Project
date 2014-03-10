#include "box3Dcollision.h"
#include "box3DglobalRule.h"
#include "Cube.cpp"
#include "Sphere.cpp"
#include "Cylinder.cpp"
#include "Plane.cpp"
void checkCollisionSphereCube(Sphere sp1,vector<Cube> cu){
	vec3 spPos = sp1.getPos();
	float radius = sp1.getRadius();
	for(int j=0;j<cu.size();j++){
		Cube cu1 = cu.at(j);
		vec3 d = cu1.getPos() - spPos;
		vec3 point = normalize(d)*radius;
		if(point.x>=cu1.getMin().x && point[0]<=cu1.getMax().x
			&& point.y>=cu1.getMin().y && point[1]<=cu1.getMax().y
			&& point.z>=cu1.getMin().z && point[2]<=cu1.getMax().z) {


		}
	}
}
void checkCollisionSphereCylinder(Sphere sp1,vector<Cylinder> cy){

}
void checkCollisionSpherePlane(Sphere sp1,vector<Plane> pl){
	float radius = sp1.getRadius();
	for(int j=0;j<pl.size();j++){
		Plane pl1 = pl.at(j);
		vec3 d = sp1.getPos() - pl1.getPos();
		float distance = d.length();
		if(distance<=radius) {


		}
	}
}

void checkCollisionSphereSphere(Sphere sp1, vector<Sphere> sp, int i){
	vec3 spPos = sp1.getPos();
	float radius = sp1.getRadius();
	for(int j=i;j<sp.size();j++){
		Sphere sp2 = sp.at(j);
		vec3 d = spPos - sp2.getPos();
		float distance = d.length();
		float sumR = radius + sp2.getRadius();
		if(distance<=sumR) {


		}
	}
}
void checkCollisionPlaneCube(Plane pl1,vector<Cube> cu){
	float plPos = pl1.getPos()[1];
	for(int j=0;j<cu.size();j++){
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
	vec3 cu1Max = cu1.getMax();
	vec3 cu1Min = cu1.getMin();
	for(int j=i;j<cu.size();j++){
		Cube cu2 = cu.at(j);
		if(cu1Max.x>=cu2.getMin().x && cu1Min[0]<=cu2.getMax().x
			&& cu1Max.y>=cu2.getMin().y && cu1Min[1]<=cu2.getMax().y
			&& cu1Max.z>=cu2.getMin().z && cu1Min[2]<=cu2.getMax().z) {


		}
	}
}
void checkCollisionCubeCylinder(Cube cu1,vector<Cylinder> cy){

}
void checkCollisionCylinderCylinder(Cylinder cy1,vector<Cylinder> cy,int i){

}

void checkCollision(vector<Cube> cu, vector<Cylinder> cy, vector<Plane> pl, vector<Sphere> sp){
	for(int i=0;i<sp.size();i++){
		Sphere sp1 = sp.at(i);
		checkCollisionSphereCube(sp1,cu);
		checkCollisionSphereCylinder(sp1,cy);
		checkCollisionSpherePlane(sp1,pl);
		checkCollisionSphereSphere(sp1,sp,i+1);
	}
	for(int i=0;i<pl.size();i++){
		Plane pl1 = pl.at(i);
		checkCollisionPlaneCube(pl1,cu);
		checkCollisionPlaneCylinder(pl1,cy);
		checkCollisionPlanePlane(pl1,pl,i+1);
	}
	for(int i=0;i<cu.size();i++){
		Cube cu1 = cu.at(i);
		checkCollisionCubeCube(cu1,cu,i+1);
		checkCollisionCubeCylinder(cu1,cy);
	}
	for(int i=0;i<cy.size();i++){
		Cylinder cy1 = cy.at(i);
		checkCollisionCylinderCylinder(cy1,cy,i+1);
	}
}



