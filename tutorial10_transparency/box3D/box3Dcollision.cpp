#include "box3Dcollision.h"
#include "box3DglobalRule.h"
#include "box3DcalculateForce.cpp"


float minn(float x, float y){
	return (x < y ?  x : y) ;
}
//completed with intersection
void checkCollision_SphereCube(Sphere sp1,Cube cube){
	vec4 dist = sp1.position-cube.position;
	vec4 surfaceSp1 = dist*( (dist.length()-sp1.radius) / dist.length() );
	vec4 point = cube.getInverseRatationMatrix()*surfaceSp1;
	vec3 cubeSkin = cube.getSkin();
	if(abs(point.x)<=cubeSkin.x && abs(point.y)<=cubeSkin.y && abs(point.z)<=cubeSkin.z) {

		//onCollision
		colSphere_Cube(sp1,cube);
	}

}
void checkCollision_SphereCylinder(Sphere sph,Cylinder cyl){
	vec4 spherePos = cyl.getInverseRatationMatrix()*(sph.position-cyl.position);
	vec4 cylNormal = vec4(0,1,0,0);
	float projectDist = dot(spherePos,cylNormal);
	vec4 minDist = projectDist*cylNormal-spherePos;
	if(minDist.length() >= cyl.radius + sph.radius) return;
	if(minDist.length() < cyl.radius){
		if(projectDist <= cyl.length + sph.radius) return;
		else colSphere_Cylinder(sph,cyl);
	} else {
		
	}
}
//completed
void checkCollision_SpherePlane(Sphere sp1,Plane pl1){
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
void checkCollision_SphereSphere(Sphere sp1, Sphere sp2){
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
void checkCollision_PlaneCube(Plane pl1,Cube cu1){
	vec4 plPos = pl1.position;
	vec4 plNormal = pl1.getNormal();
	vec4 temp = cu1.position-pl1.position;
	float distance = dot(temp,plNormal);
}
//conpleted
void checkCollision_PlaneCylinder(Plane pl,Cylinder cylinder){
	vec4 dist = cylinder.position-pl.position;
	vec4 cylinderPosition_PlaneModel = pl.getInverseRatationMatrix()*dist;
	vec4 cylinderNormal_PlaneModel = pl.getInverseRatationMatrix()*cylinder.getRotationMatrix()*vec4(0,1,0,0);
	float height = dot(cylinderNormal_PlaneModel,vec4(0,1,0,0)) + (cross(vec3(0,1,0),vec3(cylinderNormal_PlaneModel))*cylinder.radius).length();
	if(height<=cylinder.position.y){
		//Collision
		colPlane_Cylinder(pl,cylinder);
	}
}

void checkCollision_CubeCube(Cube cu1,Cube cu2){
	vec3 cu1Max = cu1.getMax();
	vec3 cu1Min = cu1.getMin();
	if(cu1Max.x>=cu2.getMin().x && cu1Min.x<=cu2.getMax().x
		&& cu1Max.y>=cu2.getMin().y && cu1Min.y<=cu2.getMax().y
		&& cu1Max.z>=cu2.getMin().z && cu1Min.z<=cu2.getMax().z) {
			//onCollision

	}
}
void checkCollision_CubeCylinder(Cube cu1,Cylinder cylinder){
	
}
void checkCollision_CylinderCylinder(Cylinder cylinder1,Cylinder cylinder2){
	vec4 cylinder1Normal = cylinder1.getNormal();
	vec4 cylinder1Center = cylinder1.position;
	//vec4 ep1 = cylinder2.getEndPoint1();
	//vec4 ep2 = cylinder2.getEndPoint2();
	//vec4 centerVec1 = ep1 - cylinder1Center;
	//vec4 centerVec2 = ep2 - cylinder1Center;
	//float distance = minn(dot(centerVec1,cylinder1Normal),dot(centerVec2,cylinder1Normal));
	//if(distance<=cylinder1.radius+cylinder2.radius){
	//	//oncollision
	//}

}
void checkCollision_(vector<Cube> cu, vector<Cylinder> cylinder, vector<Plane> pl, vector<Sphere> sp){
	for(int i=0;i<sp.size();i++){
		Sphere sp1 = sp.at(i);
		for(int j=0;j<cu.size();j++) checkCollision_SphereCube(sp1,cu.at(j));
		for(int j=0;j<cylinder.size();j++) checkCollision_SphereCylinder(sp1,cylinder.at(j));
		for(int j=0;j<pl.size();j++) checkCollision_SpherePlane(sp1,pl.at(j));
		for(int j=i+1;j<sp.size();j++) checkCollision_SphereSphere(sp1,sp.at(j));
	}
	for(int i=0;i<pl.size();i++){
		Plane pl1 = pl.at(i);
		for(int j=0;j<cu.size();j++) checkCollision_PlaneCube(pl1,cu.at(j));
		for(int j=0;j<cu.size();j++) checkCollision_PlaneCylinder(pl1,cylinder.at(j));
	}
	for(int i=0;i<cu.size();i++){
		Cube cu1 = cu.at(i);
		for(int j=i+1;j<cu.size();j++) checkCollision_CubeCube(cu1,cu.at(j));
		for(int j=0;j<cu.size();j++) checkCollision_CubeCylinder(cu1,cylinder.at(j));
	}
	for(int i=0;i<cylinder.size()-1;i++){
		Cylinder cylinder1 = cylinder.at(i);
		for(int j=i+1;j<cylinder.size();j++) checkCollision_CylinderCylinder(cylinder1,cylinder.at(j));

	}
}



