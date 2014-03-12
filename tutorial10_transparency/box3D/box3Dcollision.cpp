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
	//GridCell gridcell [gridSize][gridSize];
	Grid(int n){

	}
};


float inline minn(float x, float y){
	return (x < y ?  x : y) ;
}
//some intersection
//not test
void inline checkCollision_SphereCube(Sphere sph,Cube cube){
	if(projectSize(cube.velocity - sph.velocity,cube.position - sph.position) >= 0) return;
	vec4 dist = sph.position-cube.position;
	vec4 surfaceSp1 = dist*( length(dist) - sph.radius) / length(dist) ;
	vec4 point = cube.getInverseRatationMatrix()*surfaceSp1;
	vec3 cubeSkin = cube.getSkin();
	if(abs(point.x)<=cubeSkin.x && abs(point.y)<=cubeSkin.y && abs(point.z)<=cubeSkin.z) {
		//onCollision
		colSphere_Cube(sph,cube);
	}

}
//not test
void inline checkCollision_SphereCylinder(Sphere sph,Cylinder cyl){
	if(projectSize(cyl.velocity - sph.velocity,cyl.position - sph.position) >= 0) return;
	vec4 spherePos = cyl.getInverseRatationMatrix()*(sph.position-cyl.position);
	vec4 cylNormal = vec4(0,1,0,0);
	float projectDist = projectSize(spherePos,cylNormal);
	vec4 minDist = projectDist*cylNormal-spherePos;
	if(length(minDist) >= cyl.radius + sph.radius) return;
	if(length(minDist) < cyl.radius){
		if(projectDist <= cyl.length + sph.radius) return;
		else colSphere_Cylinder(sph,cyl);
	} else {
		if(length(projectDist*cylNormal + vec4(cyl.radius,0,0,0) - spherePos) >= sph.radius) return;
		else colSphere_Cylinder(sph,cyl);
	}
}
//not test
void inline checkCollision_SpherePlane(Sphere sph1,Plane plane2){
	if(projectSize(plane2.velocity - sph1.velocity,plane2.position - sph1.position) >= 0) return;
	vec4 spPos = sph1.position;
	float radius = sph1.radius;
	vec4 centerVec = spPos-plane2.position;
	float distance = projectSize(centerVec,plane2.getNormal());
	if(distance<=radius) {
		//onCollision
		colSphere_Plane(sph1,plane2);
	}

}
//not test
void inline checkCollision_SphereSphere(Sphere sph1, Sphere sph2){
	if(projectSize(sph2.velocity - sph1.velocity,sph2.position - sph1.position) >= 0) return;
	vec4 sphPos = sph1.position;
	float radius = sph1.radius;
	vec4 d = sphPos - sph2.position;
	float distance = length(d);
	float sumR = radius + sph2.radius;
	if(distance<=sumR) {
		//onCollision
		colSphere_Sphere(sph1,sph2);
	}
}
//dummy collision
//not test
void inline checkCollision_PlaneCube(Plane plane,Cube cube){
	if(projectSize(cube.velocity - plane.velocity,cube.position - plane.position) >= 0) return;
	//vec4 cubeHeight_ModelPlane = projectVec(cube.position - plane.position,plane.getNormal());
	float cubeHeight_ModelPlane = projectSize(cube.position-plane.position,plane.getNormal());
	if(cubeHeight_ModelPlane >= cube.maxRadius) return;
	else colCube_Plane(cube,plane);
}
//not test
void inline checkCollision_PlaneCylinder(Plane plane,Cylinder cylinder){
	if(projectSize(cylinder.velocity - plane.velocity,cylinder.position - plane.position) >= 0) return;
	vec4 dist = cylinder.position-plane.position;
	vec4 cylinderPosition_PlaneModel = plane.getInverseRatationMatrix()*dist;
	vec4 cylinderNormal_PlaneModel = plane.getInverseRatationMatrix()*cylinder.getRotationMatrix()*vec4(0,1,0,0);
	float height = projectSize(cylinderNormal_PlaneModel,vec4(0,1,0,0)) + length(cross(vec3(0,1,0),vec3(cylinderNormal_PlaneModel))*cylinder.radius);
	if(height<=cylinder.position.y){
		//Collision
		colPlane_Cylinder(plane,cylinder);
	}
}

void inline checkCollision_CubeCube(Cube cube1,Cube cube2){
	if(projectSize(cube2.velocity - cube1.velocity,cube2.position - cube1.position) >= 0) return;
}
void inline checkCollision_CubeCylinder(Cube cube1,Cylinder cyl2){
	if(projectSize(cyl2.velocity - cube1.velocity,cyl2.position - cube1.position) >= 0) return;
}
void inline checkCollision_CylinderCylinder(Cylinder cylinder1,Cylinder cylinder2){
	if(projectSize(cylinder2.velocity - cylinder1.velocity,cylinder2.position - cylinder1.position) >= 0) return;
	float minimumDist = dist3D_Segment_to_Segment(cylinder1.getEndPoint1(),cylinder1.getEndPoint2(),cylinder2.getEndPoint1(),cylinder2.getEndPoint2());
	if(minimumDist >= cylinder1.radius + cylinder2.radius) return;
	else if(minimumDist <= cylinder1.radius) colCylinder_Cylinder(cylinder1,cylinder2);
	else{/*
		if(){}
		else{
			normalize()
		}*/
	}
}

vec4 inline directionToPos(vec4 pos1,vec4 pos2){
	return pos2-pos1;
}

bool inline isMoveout(Rigidbody* obj1,Rigidbody* obj2){
	if(projectSize(obj2->velocity - obj1->velocity,obj2->position - obj1->position) >= 0) return true;
	else return false;
}

void inline checkCollision(vector<Cube> cu, vector<Cylinder> cy, vector<Plane> pl, vector<Sphere> sp){
	for(int i=0;i<sp.size();i++){
			Sphere sp1 = sp.at(i);
			for(int j=0;j<cu.size();j++) checkCollision_SphereCube(sp1,cu.at(j));
			for(int j=0;j<cy.size();j++) checkCollision_SphereCylinder(sp1,cy.at(j));
			for(int j=0;j<pl.size();j++) checkCollision_SpherePlane(sp1,pl.at(j));
			for(int j=i+1;j<sp.size();j++) checkCollision_SphereSphere(sp1,sp.at(j));
		}
		for(int i=0;i<pl.size();i++){
			Plane pl1 = pl.at(i);
			for(int j=0;j<cu.size();j++) checkCollision_PlaneCube(pl1,cu.at(j));
			for(int j=0;j<cy.size();j++) checkCollision_PlaneCylinder(pl1,cy.at(j));
		}
		for(int i=0;i<cu.size();i++){
			Cube cu1 = cu.at(i);
			for(int j=i+1;j<cu.size();j++) checkCollision_CubeCube(cu1,cu.at(j));
			for(int j=0;j<cy.size();j++) checkCollision_CubeCylinder(cu1,cy.at(j));
		}
		for(int i=0;i<cy.size()-1;i++){
			Cylinder cy1 = cy.at(i);
			for(int j=i+1;j<cy.size();j++) checkCollision_CylinderCylinder(cy1,cy.at(j));
		}
}
