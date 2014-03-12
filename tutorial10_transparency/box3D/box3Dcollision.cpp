#include "box3Dcollision.h"
#include "box3DglobalRule.h"
#include "box3DcalculateForce.cpp"

#define gridSize 10

class GridCell
{
public:
	vector<Cube> cube;
	vector<Cylinder> cylinder;
	vector<Sphere> sphere;
	vector<Plane> plane;
	GridCell(){
	
	}
	GridCell(vector<Cube> cu,vector<Cylinder> cy,vector<Sphere> sp, vector<Plane>pl){
		cube = cu;
		cylinder = cy;
		sphere = sp;
		plane = pl;
	}

};

class Grid
{
public:
	GridCell gridcell [gridSize][gridSize];
	Grid(int n){

	}
};

float minn(float x, float y){
	return (x < y ?  x : y) ;
}
//completed with intersection
void checkCollisionSphereCube(Sphere sp1,Cube cube){
	vec4 dist = sp1.position-cube.position;
	vec4 surfaceSp1 = dist*( (dist.length()-sp1.radius) / dist.length() );
	vec4 point = cube.getInverseRatationMatrix()*surfaceSp1;
	vec3 cubeSkin = cube.getSkin();
	if(abs(point.x)<=cubeSkin.x && abs(point.y)<=cubeSkin.y && abs(point.z)<=cubeSkin.z) {

		//onCollision
		colSphere_Cube(sp1,cube);
	}

}
void checkCollisionSphereCylinder(Sphere sp1,Cylinder cy1){
	//vec4 spPos = sp1.position;
	//float radius = sp1.radius;
	//vec4 ep1 = cy1.getEndPoint1();
	//vec4 ep2 = cy1.getEndPoint2();
	//vec4 centerVec1 = ep1-spPos;
	//vec4 centerVec2 = ep2-spPos;
	////float distance = minn(centerVec1.length(),center); 
	//if(distance<=radius) {
	//onCollision
	//}

}
//completed
void checkCollisionSpherePlane(Sphere sp1,Plane pl1){
	vec4 spPos = sp1.position;
	float radius = sp1.radius;
	vec4 centerVec = spPos-pl1.position;
	float distance = dot(centerVec,pl1.getNormal());
	if(distance<=radius) {
		//onCollision
		colSphere_Plane(sp1,pl1);
	}

}
//completed
void checkCollisionSphereSphere(Sphere sp1, Sphere sp2){
	vec4 spPos = sp1.position;
	float radius = sp1.radius;
	vec4 d = spPos - sp2.position;
	float distance = d.length();
	float sumR = radius + sp2.radius;
	if(distance<=sumR) {
		//onCollision
		colSphere_Sphere(sp1,sp2);
	}
}
void checkCollisionPlaneCube(Plane pl1,Cube cu1){
	vec4 plPos = pl1.position;
	vec4 plNormal = pl1.getNormal();
	vec4 temp = cu1.position-pl1.position;
	float distance = dot(temp,plNormal);
}
void checkCollisionPlaneCylinder(Plane pl,Cylinder cy){
	vec4 dist = cy.position-pl.position;
	vec4 cyPositionPlaneModel = pl.getInverseRatationMatrix()*dist;
	vec4 cyNormalPlaneModel = pl.getInverseRatationMatrix()*cy.getRotationMatrix()*vec4(0,1,0,0);
	float height = dot(vec3(cyNormalPlaneModel),vec3(0,1,0));
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
	vec4 cy1Normal = cy1.getNormal();
	vec4 cy1Center = cy1.position;
	//vec4 ep1 = cy2.getEndPoint1();
	//vec4 ep2 = cy2.getEndPoint2();
	//vec4 centerVec1 = ep1 - cy1Center;
	//vec4 centerVec2 = ep2 - cy1Center;
	//float distance = minn(dot(centerVec1,cy1Normal),dot(centerVec2,cy1Normal));
	//if(distance<=cy1.radius+cy2.radius){
	//	//oncollision
	//}

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



