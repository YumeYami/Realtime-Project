#include "box3Dcollision.h"
#include "box3DglobalRule.h"
#include "box3DcalculateForce.cpp"
void checkCollisionSphereCube(Sphere sp1,Cube cube){
	vec3 dist = sp1.getPos()-cube.getPos();
	vec3 surfaceSp1 = dist*( (dist.length()-sp1.getRadius()) / dist.length() );
	vec4 point = cube.getInverseRatationMatrix()*vec4(surfaceSp1,1.0f);
	vec3 cubeSkin = cube.getSkin();
	if(abs(point.x)<=cubeSkin.x && abs(point.y)<=cubeSkin.y && abs(point.z)<=cubeSkin.z) {
			//onCollision
		colSphere_Cube(sp1,cube,vec3(point));
	}

}
void checkCollisionSphereCylinder(Sphere sp1,Cylinder cy1){
	vec3 spPos = sp1.getPos();
	float radius = sp1.getRadius();
	
	
		vec3 ep1 = cy1.getEndPoint1();
		//vec3 ep2 = cy1.getEndPoint2();
		//vec3 cyVector = ep2-ep1;
		vec3 centerVec = spPos-ep1;
		float distance = dot(centerVec,cy1.getNormal());
		if(distance!=0) distance=distance-cy1.getRadius();
		if(distance<=radius) {
			//onCollision

		}
	
}

void checkCollisionSpherePlane(Sphere sp1,Plane pl1){
	vec3 spPos = sp1.getPos();
	float radius = sp1.getRadius();
	
		
		vec3 centerVec = spPos-pl1.getPos();
		float distance = dot(centerVec,normalize(pl1.getNormal()));
		if(distance<=radius) {
			//onCollision

		}
	
}

void checkCollisionSphereSphere(Sphere sp1, Sphere sp2){
	vec3 spPos = sp1.getPos();
	float radius = sp1.getRadius();

		vec3 d = spPos - sp2.getPos();
		float distance = d.length();
		float sumR = radius + sp2.getRadius();
		if(distance<=sumR) {
			//onCollision

		}
	
}
void checkCollisionPlaneCube(Plane pl1,Cube cu1){
	vec3 plPos = pl1.getPos();
	vec3 plNormal = pl1.getNormal();

		vec3 temp = cu1.getPos()-plPos;
		float distance = dot(temp,plNormal);
		//if(distance<=) {
		//onCollision

		//}
	
}
void checkCollisionPlaneCylinder(Plane pl1,Cylinder cy){

}


void checkCollisionCubeCube(Cube cu1,Cube cu2){
	vec3 cu1Max = cu1.getMax();
	vec3 cu1Min = cu1.getMin();

		if(cu1Max.x>=cu2.getMin().x && cu1Min.x<=cu2.getMax().x
			&& cu1Max.y>=cu2.getMin().y && cu1Min.y<=cu2.getMax().y
			&& cu1Max.z>=cu2.getMin().z && cu1Min.z<=cu2.getMax().z) {
				//onCollision

		}
	
}
void checkCollisionCubeCylinder(Cube cu1,Cylinder cy){

}
void checkCollisionCylinderCylinder(Cylinder cy1,Cylinder cy2){
	vec3 ep1cy1 = cy1.getEndPoint1();
	vec3 ep1cy2 = cy2.getEndPoint1();

}

void checkCollision(vector<Cube> cu, vector<Cylinder> cy, vector<Plane> pl, vector<Sphere> sp){
	for(int i=0;i<sp.size();i++){
		Sphere sp1 = sp.at(i);
		for(int j=0;j<cu.size();j++) checkCollisionSphereCube(sp1,cu.at(j));
		for(int j=0;j<cy.size();j++) checkCollisionSphereCylinder(sp1,cy.at(j));
		for(int j=0;j<pl.size();j++) checkCollisionSpherePlane(sp1,pl.at(j));
		for(int j=i+1;j<sp.size();j++) checkCollisionSphereSphere(sp1,sp.at(j));
	}
	for(int i=0;i<pl.size();i++){
		Plane pl1 = pl.at(i);
		for(int j=0;j<cu.size();j++) checkCollisionPlaneCube(pl1,cu.at(j));
		for(int j=0;j<cu.size();j++) checkCollisionPlaneCylinder(pl1,cy.at(j));
	}
	for(int i=0;i<cu.size();i++){
		Cube cu1 = cu.at(i);
		for(int j=i+1;j<cu.size();j++) checkCollisionCubeCube(cu1,cu.at(j));
		for(int j=0;j<cu.size();j++) checkCollisionCubeCylinder(cu1,cy.at(j));
	}
	for(int i=0;i<cy.size()-1;i++){
		Cylinder cy1 = cy.at(i);
		for(int j=i+1;j<cy.size();j++) checkCollisionCylinderCylinder(cy1,cy.at(j));
		
	}
}



