#include "box3Dcollision.h"
#include "box3DglobalRule.h"
#include "box3DcalculateForce.cpp"
#define gridSize 10
#define ftl_x -5
#define ftl_y 5
#define ftl_z 5
#define backDownRight vec3(5,-5,-5);


float inline minn(float x, float y){
	return (x < y ?  x : y) ;
}
//completed with intersection
void inline checkCollision_SphereCube(Sphere sph,Cube cube){
	if(dot(cube.velocity - sph.velocity,cube.position - sph.position) >= 0) return;
	vec4 dist = sph.position-cube.position;
	vec4 surfaceSp1 = dist*( (dist.length()-sph.radius) / dist.length() );
	vec4 point = cube.getInverseRatationMatrix()*surfaceSp1;
	vec3 cubeSkin = cube.getSkin();
	if(abs(point.x)<=cubeSkin.x && abs(point.y)<=cubeSkin.y && abs(point.z)<=cubeSkin.z) {

		//onCollision
		colSphere_Cube(sph,cube);
	}

}
//completed
void inline checkCollision_SphereCylinder(Sphere sph,Cylinder cyl){
	vec4 spherePos = cyl.getInverseRatationMatrix()*(sph.position-cyl.position);
	vec4 cylNormal = vec4(0,1,0,0);
	float projectDist = dot(spherePos,cylNormal);
	vec4 minDist = projectDist*cylNormal-spherePos;
	if(minDist.length() >= cyl.radius + sph.radius) return;
	if(minDist.length() < cyl.radius){
		if(projectDist <= cyl.length + sph.radius) return;
		else colSphere_Cylinder(sph,cyl);
	} else {
		if((projectDist*cylNormal + vec4(cyl.radius,0,0,0) - spherePos).length() >= sph.radius) return;
		else colSphere_Cylinder(sph,cyl);
	}
}
//completed
void inline checkCollision_SpherePlane(Sphere sp1,Plane pl1){
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
void inline checkCollision_SphereSphere(Sphere sp1, Sphere sp2){
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
void inline checkCollision_PlaneCube(Plane pl1,Cube cu1){
	vec4 plPos = pl1.position;
	vec4 plNormal = pl1.getNormal();
	vec4 temp = cu1.position-pl1.position;
	float distance = dot(temp,plNormal);
}
//conpleted
void inline checkCollision_PlaneCylinder(Plane pl,Cylinder cylinder){
	vec4 dist = cylinder.position-pl.position;
	vec4 cylinderPosition_PlaneModel = pl.getInverseRatationMatrix()*dist;
	vec4 cylinderNormal_PlaneModel = pl.getInverseRatationMatrix()*cylinder.getRotationMatrix()*vec4(0,1,0,0);
	float height = dot(cylinderNormal_PlaneModel,vec4(0,1,0,0)) + (cross(vec3(0,1,0),vec3(cylinderNormal_PlaneModel))*cylinder.radius).length();
	if(height<=cylinder.position.y){
		//Collision
		colPlane_Cylinder(pl,cylinder);
	}
}

void inline checkCollision_CubeCube(Cube cu1,Cube cu2){
}
void inline checkCollision_CubeCylinder(Cube cu1,Cylinder cylinder){
}
void inline checkCollision_CylinderCylinder(Cylinder cylinder1,Cylinder cylinder2){
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

bool inline isMoveout(Rigidbody* obj1,Rigidbody* obj2){
	if(dot(obj2->velocity - obj1->velocity,obj2->position - obj1->position) >= 0) return true;
	else return false;
}

void inline checkCollision(vector<Cube> cu, vector<Cylinder> cy, vector<Plane> pl, vector<Sphere> sp){
	for(int i=0;i<sp.size();i++){
		Sphere sp1 = sp.at(i);
		for(int j=0;j<cu.size();j++) checkCollision_SphereCube(sp1,cu.at(j));
		for(int j=0;j<cy.size();j++) checkCollision_SphereCylinder(sp1,cy.at(j));
		for(int j=0;j<pl.size();j++) checkCollision_SpherePlane(sp1,pl.at(j));
		if(i<sp.size()-1) for(int j=i+1;j<sp.size();j++) checkCollision_SphereSphere(sp1,sp.at(j));
	}
	for(int i=0;i<pl.size();i++){
		Plane pl1 = pl.at(i);
		for(int j=0;j<cu.size();j++) checkCollision_PlaneCube(pl1,cu.at(j));
		for(int j=0;j<cy.size();j++) checkCollision_PlaneCylinder(pl1,cy.at(j));
	}
	for(int i=0;i<cu.size();i++){
		Cube cu1 = cu.at(i);
		if(i<cu.size()-1) for(int j=i+1;j<cu.size();j++) checkCollision_CubeCube(cu1,cu.at(j));
		for(int j=0;j<cy.size();j++) checkCollision_CubeCylinder(cu1,cy.at(j));
	}
	for(int i=0;i<cy.size();i++){
		Cylinder cy1 = cy.at(i);
		if(i<cy.size()-1) 
			for(int j=i+1;j<cy.size();j++)
				checkCollision_CylinderCylinder(cy1,cy.at(j));

	}
}


class GridCell
{
public:
	vector<Cube> cube;
	vector<Cylinder> cylinder;
	vector<Sphere> sphere;
	vector<Plane> plane;
	GridCell(){}
	void addCubeToGridCell(Cube cu){
		cube.push_back(cu);
	}
	void addCylinderToGridCell(Cylinder cy){
		cylinder.push_back(cy);
	}
	void addSphereToGridCell(Sphere sp){
		sphere.push_back(sp);
	}
	void addPlaneToGridCell(Plane pl){
		plane.push_back(pl);
	}
	void clearGridCell(){
		cube.clear();
		cylinder.clear();
		sphere.clear();
	}
	void checkCollisionGridCell(){
		checkCollision(cube,cylinder,plane,sphere);
	}

};
class Grid
{
public:
	GridCell gridcell[gridSize][gridSize][gridSize];
	float width;
	Grid(){}
	Grid(vector<Cube> cu,vector<Cylinder> cy,vector<Sphere> sp, vector<Plane>pl){
		width = 10/gridSize;
		for(int i=0;i<gridSize;i++)
			for(int j=0;j<gridSize;j++)
				for(int k=0;k<gridSize;k++)
					gridcell[i][j][k] = GridCell();
		//gridcell[i][j][k] = GridCell(ftl_x+width*i,ftl_y+width*j,ftl_z+width*k);
		hashGrid(cu,cy,sp);
		for(int i=0;i<pl.size();i++) hashPlane(pl[i]);
	};

	void hashGrid(vector<Cube> cu,vector<Cylinder> cy,vector<Sphere> sp){
		for(int i=0;i<cu.size();i++) hashCube(cu[i]);
		for(int i=0;i<cy.size();i++) hashCylinder(cy[i]);
		for(int i=0;i<sp.size();i++) hashSphere(sp[i]);
	}


	void hashCube(Cube r){
		vec4 pos = r.position;
		vec3 index = findIndex(vec3(pos.x,pos.y,pos.z));
		for(int i=index.x-1;i<=index.x+1;i++)
			for(int j=index.y-1;j<=index.y+1;j++)
				for(int k=index.z-1;k<=index.z+1;k++)
					if(i>=0 && j>=0 && k>=0) gridcell[i][j][k].addCubeToGridCell(r);
	}
	void hashCylinder(Cylinder r){
		vec4 pos = r.position;
		vec3 index = findIndex(vec3(pos.x,pos.y,pos.z));
		for(int i=index.x-1;i<=index.x+1;i++)
			for(int j=index.y-1;j<=index.y+1;j++)
				for(int k=index.z-1;k<=index.z+1;k++)
					if(i>=0 && j>=0 && k>=0) gridcell[i][j][k].addCylinderToGridCell(r);
	}
	void hashSphere(Sphere r){
		vec4 pos = r.position;
		vec3 index = findIndex(vec3(pos.x,pos.y,pos.z));
		for(int i=index.x-1;i<=index.x+1;i++)
			for(int j=index.y-1;j<=index.y+1;j++)
				for(int k=index.z-1;k<=index.z+1;k++)
					if(i>=0 && j>=0 && k>=0) gridcell[i][j][k].addSphereToGridCell(r);
	}
	void hashPlane(Plane r){
		vec4 pos = r.position;
		vec3 index = findIndex(vec3(pos.x,pos.y,pos.z));
		for(int i=index.x-1;i<=index.x+1;i++)
			for(int j=index.y-1;j<=index.y+1;j++)
				for(int k=index.z-1;k<=index.z+1;k++)
					if(i>=0 && j>=0 && k>=0) gridcell[i][j][k].addPlaneToGridCell(r);
	}
	vec3 findIndex(vec3 pos){
		vec3 index;
		index.x = (pos.x-ftl_x)/width;
		index.y = (pos.y-ftl_y)/width;
		index.z = (pos.z-ftl_z)/width;
		return index;
	}

	void clearGrid(){
		for(int i=0;i<gridSize;i++)
			for(int j=0;j<gridSize;j++)
				for(int k=0;k<gridSize;k++)
					gridcell[i][j][k].clearGridCell();

	}
	void checkCollisionGrid(){
		for(int i=0;i<gridSize;i++)
			for(int j=0;j<gridSize;j++)
				for(int k=0;k<gridSize;k++){
					gridcell[i][j][k].checkCollisionGridCell();
				}
	}
};

