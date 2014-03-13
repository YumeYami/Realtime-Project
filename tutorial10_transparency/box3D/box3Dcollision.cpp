#include "box3Dcollision.h"
#include "box3DglobalRule.h"
#include "box3DcalculateForce.cpp"

#define gridSize 13
#define begin_x -5
#define begin_y -5
#define begin_z -5

float inline minn(float x, float y){
	return (x < y ?  x : y) ;
}
//complete
void inline checkCollision_SphereCube(Sphere* sph1,Cube* cube2){
	if(projectSize(cube2->velocity - sph1->velocity,cube2->position - sph1->position) >= 0) return;
	//cout<<"check cube\n";
	for (int i = 0; i < 12; i++)
	{
		vec4 start = (cube2->edgeSta[i]);
		vec4 end = (cube2->edgeEnd[i]);
		vec4 colPoint =  dist3D_Segment_to_point(start,end,sph1->position);
		if (length(colPoint) <= sph1->radius){
			cout<<"collision Cube";
			colSphere_Cube(sph1,cube2,colPoint);
			return;
		}
	}
}
//not test
void inline checkCollision_SphereCylinder(Sphere* sph1,Cylinder* cylinder2){
	if(projectSize(cylinder2->velocity - sph1->velocity,cylinder2->position - sph1->position) >= 0) return;
	vec4 spherePos = cylinder2->getInverseRatationMatrix()*(sph1->position-cylinder2->position);
	vec4 cylNormal = vec4(0,1,0,0);
	float projectDist = projectSize(spherePos,cylNormal);
	vec4 minDist = projectDist*cylNormal-spherePos;
	if(length(minDist) >= cylinder2->radius + sph1->radius) return;
	if(length(minDist) < cylinder2->radius){
		if(projectDist <= cylinder2->length + sph1->radius) return;
		else colSphere_Cylinder(sph1,cylinder2);
	} else {
		if(length(projectDist*cylNormal + vec4(cylinder2->radius,0,0,0) - spherePos) >= sph1->radius) return;
		else colSphere_Cylinder(sph1,cylinder2);
	}
}
//completed
void inline checkCollision_SpherePlane(Sphere* sph1,Plane* plane2){
	if(projectSize(sph1->velocity,plane2->getNormal()) >= 0) return;
	vec4 spPos = sph1->position;
	float radius = sph1->radius;
	vec4 centerVec = spPos - plane2->position;
	vec4 height = projectVec(centerVec,plane2->getNormal());
	if(length(height)<=radius) {
		colSphere_Plane(sph1,plane2,height);
	}

}
//completed
void inline checkCollision_SphereSphere(Sphere* sph1, Sphere* sph2){
	if(projectSize(sph2->velocity - sph1->velocity,sph2->position - sph1->position) >= 0) return;
	vec4 sphPos = sph1->position;
	float radius = sph1->radius;
	vec4 d = sphPos - sph2->position;
	float distance = length(d);
	float sumR = radius + sph2->radius;
	if(distance<=sumR) {
		//onCollision
		colSphere_Sphere(sph1,sph2);
	}
}
//not test
void inline checkCollision_PlaneCube(Plane* plane1,Cube* cube2){
	if(projectSize(cube2->velocity - plane1->velocity,cube2->position - plane1->position) >= 0) return;
	//vec4 cubeHeight_ModelPlane* = projectVec(cube2->position - plane1->position,plane1->getNormal());
	float cubeHeight_ModelPlane = projectSize(cube2->position-plane1->position,plane1->getNormal());
	if(cubeHeight_ModelPlane >= cube2->maxRadius) return;
	else colCube_Plane(cube2,plane1);
	//cout<<"check plane cube\n";
}
//not test
void inline checkCollision_PlaneCylinder(Plane* plane1,Cylinder* cylinder2){
	if(projectSize(cylinder2->velocity - plane1->velocity,cylinder2->position - plane1->position) >= 0) return;
	vec4 dist = cylinder2->position-plane1->position;
	vec4 cylinderPosition_PlaneModel = plane1->getInverseRatationMatrix()*dist;
	vec4 cylinderNormal_PlaneModel = plane1->getInverseRatationMatrix()*cylinder2->getRotationMatrix()*vec4(0,1,0,0);
	float height = projectSize(cylinderNormal_PlaneModel,vec4(0,1,0,0)) + length(cross(vec3(0,1,0),vec3(cylinderNormal_PlaneModel))*cylinder2->radius);
	if(height<=cylinder2->position.y){
		//Collision
		colPlane_Cylinder(plane1,cylinder2);
	}
}

void inline checkCollision_CubeCube(Cube* cube1,Cube* cube2){
	if(projectSize(cube2->velocity - cube1->velocity,cube2->position - cube1->position) >= 0) return;
	
}
void inline checkCollision_CubeCylinder(Cube* cube1,Cylinder* cyl2){
	if(projectSize(cyl2->velocity - cube1->velocity,cyl2->position - cube1->position) >= 0) return;

}
void inline checkCollision_CylinderCylinder(Cylinder* cylinder1,Cylinder* cylinder2){
	if(projectSize(cylinder2->velocity - cylinder1->velocity,cylinder2->position - cylinder1->position) >= 0) return;
	vec4 minimumDist = dist3D_Segment_to_Segment(cylinder1->getEndPoint1(),cylinder1->getEndPoint2(),cylinder2->getEndPoint1(),cylinder2->getEndPoint2());
	if(length(minimumDist)>= cylinder1->radius + cylinder2->radius) return;
	else if(length(minimumDist) <= cylinder1->radius) colCylinder_Cylinder(cylinder1,cylinder2);
	else{

	}
}

bool inline testPlane(Rigidbody* obj1,Plane* plane){

}
bool inline testDirection(Rigidbody* obj1, Rigidbody* obj2){
	vec4 relateVelo = obj2->velocity-obj1->velocity;

}

vec4 inline directionToPos(vec4 pos1,vec4 pos2){
	return pos2-pos1;
}


void inline checkCollision(vector<Cube*> cu, vector<Cylinder*> cy, vector<Plane*> pl, vector<Sphere*> sp){
	//cout <<"size "<<cu.size()<<" "<<cy.size()<<" "<<pl.size()<<" "<<sp.size()<<"\n";
	for(int i=0;i<sp.size();i++){
		Sphere* sp1 = sp.at(i);

		for(int j=0;j<cu.size();j++) checkCollision_SphereCube(sp1,cu.at(j));
		for(int j=0;j<cy.size();j++) checkCollision_SphereCylinder(sp1,cy.at(j));
		for(int j=0;j<pl.size();j++) {
			checkCollision_SpherePlane(sp1,pl.at(j));
			//cout<<"check\n";
		}
		if(i<sp.size()-1) 
			for(int j=i+1;j<sp.size();j++) {
				checkCollision_SphereSphere(sp1,sp.at(j));
			}
	}
	for(int i=0;i<pl.size();i++){
		Plane* pl1 = pl.at(i);
		for(int j=0;j<cu.size();j++) checkCollision_PlaneCube(pl1,cu.at(j));
		for(int j=0;j<cy.size();j++) checkCollision_PlaneCylinder(pl1,cy.at(j));
	}
	for(int i=0;i<cu.size();i++){
		Cube* cu1 = cu.at(i);
		if(i<cu.size()-1) for(int j=i+1;j<cu.size();j++) checkCollision_CubeCube(cu1,cu.at(j));
		for(int j=0;j<cy.size();j++) checkCollision_CubeCylinder(cu1,cy.at(j));
	}
	for(int i=0;i<cy.size();i++){
		Cylinder* cy1 = cy.at(i);
		if(i<cy.size()-1) 
			for(int j=i+1;j<cy.size();j++)
				checkCollision_CylinderCylinder(cy1,cy.at(j));

	}
}


class GridCell
{
public:
	vector<Cube*> cube;
	vector<Cylinder*> cylinder;
	vector<Sphere*> sphere;
	vector<Plane*> plane;
	GridCell(){}
	void addCubeToGridCell(Cube* cu){
		cube.push_back(cu);
	}
	void addCylinderToGridCell(Cylinder* cy){
		cylinder.push_back(cy);
	}
	void addSphereToGridCell(Sphere* sp){
		sphere.push_back(sp);
	}
	void addPlaneToGridCell(Plane* pl){
		//cout<<"addPlane\n";
		plane.push_back(pl);
	}
	void clearGridCellPlane(){
		plane.clear();
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
	Grid(vector<Plane*>pl){
		width = 1;
		for(int i=0;i<gridSize;i++)
			for(int j=0;j<gridSize;j++)
				for(int k=0;k<gridSize;k++)
					gridcell[i][j][k] = GridCell();
		//gridcell[i][j][k] = GridCell(begin_x+width*i,begin_y+width*j,begin_z+width*k);
		//hashGrid(cu,cy,sp);
		for(int i=0;i<pl.size();i++) {
			hashPlane((pl[i]));
		}
	};

	void hashGrid(vector<Cube*> cu,vector<Cylinder*> cy,vector<Sphere*> sp){
		for(int i=0;i<cu.size();i++) hashCube(cu[i]);
		for(int i=0;i<cy.size();i++) hashCylinder(cy[i]);
		for(int i=0;i<sp.size();i++) hashSphere(sp[i]);
	}


	void hashCube(Cube* r){

		vec4 pos = r->position;
		int a,b,c = 0;
		//findIndex(vec3(pos.x,pos.y,pos.z),a,b,c);
		vector<int> x;
		vector<int> y;
		vector<int> z;
		findGrid(vec3(pos.x,pos.y,pos.z),x,y,z);
		for(int i=0;i<x.size();i++){
			if(x[i]>=0 && x[i]< gridSize && y[i]>=0 && y[i]< gridSize && z[i]>=0 && z[i]< gridSize)
				gridcell[x[i]][y[i]][z[i]].addCubeToGridCell(r);
		}
	}
	void hashCylinder(Cylinder* r){
		vec4 pos = r->position;
		int a,b,c = 0;
		//findIndex(vec3(pos.x,pos.y,pos.z),a,b,c);
		vector<int> x;
		vector<int> y;
		vector<int> z;
		findGrid(vec3(pos.x,pos.y,pos.z),x,y,z);
		for(int i=0;i<x.size();i++){
			if(x[i]>=0 && x[i]< gridSize && y[i]>=0 && y[i]< gridSize && z[i]>=0 && z[i]< gridSize)
				gridcell[x[i]][y[i]][z[i]].addCylinderToGridCell(r);
		}
	}
	void hashSphere(Sphere* r){
		vec4 pos = r->position;
		int a,b,c = 0;
		//findIndex(vec3(pos.x,pos.y,pos.z),a,b,c);
		vector<int> x;
		vector<int> y;
		vector<int> z;
		findGrid(vec3(pos.x,pos.y,pos.z),x,y,z);
		for(int i=0;i<x.size();i++){
			if(x[i]>=0 && x[i]< gridSize && y[i]>=0 && y[i]< gridSize && z[i]>=0 && z[i]< gridSize)
				gridcell[x[i]][y[i]][z[i]].addSphereToGridCell(r);
		}
	}
	void hashPlane(Plane* r){

		vec4 pos = r->position;
		int a,b,c = 0;
		findIndex(vec3(pos.x,pos.y,pos.z),a,b,c);
		for(int i=0;i<gridSize;i++){
			for(int j=0;j<gridSize;j++){
				for(int k=0;k<gridSize;k++){
					if(r->orientation==vec3(0,0,PI/2)||r->orientation==vec3(0,0,-PI/2)){
						gridcell[a][j][k].addPlaneToGridCell(r);
					}
					if(r->orientation==vec3(PI/2,0,0)||r->orientation==vec3(-PI/2,0,0)){
						gridcell[i][j][c].addPlaneToGridCell(r);
					}
					if(r->orientation==vec3(0,0,0)||r->orientation==vec3(PI,0,0)){
						//cout<<"plane x = "<<r->orientation.x<<" y = "<<r->orientation.y<<" z = "<<r->orientation.z<<"\n";
						//cout<<"index x= "<< a<<" y= "<<b<<" z= "<<c<<"\n";
						gridcell[i][b][k].addPlaneToGridCell(r);
					}
				}
			}
		}
	}
	void findIndex(vec3 pos, int &i, int &j, int &k){
		i = (int)(pos.x-begin_x)/width;
		j = (int)(pos.y-begin_y)/width;
		k = (int)(pos.z-begin_z)/width;
	}
	void clearGridPlane(){
		for(int i=0;i<gridSize;i++)
			for(int j=0;j<gridSize;j++)
				for(int k=0;k<gridSize;k++)
					gridcell[i][j][k].clearGridCellPlane();
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

	void findGrid(vec3 pos,vector<int> &x, vector<int> &y, vector<int> &z){
		//x.push_back(a); y.push_back(b); z.push_back(c);
		//if(pos.x-floor(pos.x)==0.5 && pos.y-floor(pos.y)==0.5 && pos.z-floor(pos.z)==0.5) return;
		vec3 minPos = vec3(pos.x-width/2.0,pos.y-width/2.0,pos.z-width/2.0);
		vec3 maxPos = vec3(pos.x+width/2.0,pos.y+width/2.0,pos.z+width/2.0);
		int minA,minB,minC;
		int maxA,maxB,maxC;
		findIndex(minPos,minA,minB,minC);
		findIndex(maxPos,maxA,maxB,maxC);
		for(int i=minA;i<=maxA;i++){
			for(int j=minB;j<=maxB;j++){
				for(int k=minC;k<=maxC;k++){
					x.push_back(i); 
					y.push_back(j); 
					z.push_back(k);
				}
			}
		}
		//if(pos.x-floor(pos.x) < 0.5) {										//x<0.5 
		//	x.push_back(a-1); y.push_back(b); z.push_back(c);
		//	if(pos.y-floor(pos.y) < 0.5) {									//y<0.5
		//		x.push_back(a-1); y.push_back(b-1); z.push_back(c);
		//		if(pos.z-floor(pos.z) < 0.5) {								//z<0.5
		//			x.push_back(a-1); y.push_back(b-1); z.push_back(c-1); 
		//		} else {													//z>=0.5
		//			x.push_back(a-1); y.push_back(b-1); z.push_back(c+1); 
		//		}
		//	} else {														//y>=0.5
		//		x.push_back(a-1); y.push_back(b+1); z.push_back(c); 
		//		if(pos.z-floor(pos.z) < 0.5) {								//z<0.5
		//			x.push_back(a-1); y.push_back(b+1); z.push_back(c-1); 
		//		} else {													//z>=0.5
		//			x.push_back(a-1); y.push_back(b+1); z.push_back(c+1); 
		//		}
		//	}
		//} else {															//x>=0.5 
		//	x.push_back(a+1); y.push_back(b); z.push_back(c); 
		//	if(pos.y-floor(pos.y) < 0.5) {									//y<0.5 
		//		x.push_back(a+1); y.push_back(b-1); z.push_back(c); 
		//		if(pos.z-floor(pos.z) < 0.5) {								//z<0.5
		//			x.push_back(a+1); y.push_back(b-1); z.push_back(c-1); 
		//		} else {													//z>=0.5 
		//			x.push_back(a+1); y.push_back(b-1); z.push_back(c+1); 
		//		}
		//	} else {														//y>=0.5
		//		x.push_back(a+1); y.push_back(b+1); z.push_back(c); 
		//		if(pos.z-floor(pos.z) < 0.5) {								//z<0.5
		//			x.push_back(a+1); y.push_back(b+1); z.push_back(c-1); 
		//		} else {													//z>=0.5 
		//			x.push_back(a+1); y.push_back(b+1); z.push_back(c+1); 
		//		}
		//	}
		//}
		//
		//if(pos.y-floor(pos.y) < 0.5) {										//y<0.5
		//	x.push_back(a); y.push_back(b-1); z.push_back(c); 
		//	if(pos.z-floor(pos.z) < 0.5) {									//z<0.5
		//		x.push_back(a); y.push_back(b-1); z.push_back(c-1); 
		//	} else {														//z>=0.5
		//		x.push_back(a); y.push_back(b-1); z.push_back(c+1); 
		//	}
		//} else { 
		//	x.push_back(a); y.push_back(b+1); z.push_back(c); 
		//	if(pos.z-floor(pos.z) < 0.5) { 
		//		x.push_back(a); y.push_back(b+1); z.push_back(c-1); 
		//	} else { 
		//		x.push_back(a); y.push_back(b+1); z.push_back(c+1); 
		//	}
		//}
		//
		//if(pos.z-floor(pos.z) < 0.5) { 
		//	x.push_back(a); y.push_back(b); z.push_back(c-1); 
		//	if(pos.x-floor(pos.x) < 0.5) {
		//		x.push_back(a-1); y.push_back(b); z.push_back(c-1);
		//	} else {
		//		x.push_back(a+1); y.push_back(b); z.push_back(c-1);
		//	}
		//} else { 
		//	x.push_back(a); y.push_back(b); z.push_back(c+1); 
		//	if(pos.x-floor(pos.x) < 0.5) {
		//		x.push_back(a-1); y.push_back(b); z.push_back(c+1);
		//	} else {
		//		x.push_back(a+1); y.push_back(b); z.push_back(c+1);
		//	}
		//}
	
	}
};
