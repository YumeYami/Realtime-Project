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
//some intersection
//not test
void inline checkCollision_SphereCube(Sphere sph,Cube cube){
	if(projectSize(cube.getVelocity() - sph.getVelocity(),cube.getPosition() - sph.getPosition()) >= 0) return;
	vec4 dist = sph.getPosition()-cube.getPosition();
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
	if(projectSize(cyl.getVelocity() - sph.getVelocity(),cyl.getPosition() - sph.getPosition()) >= 0) return;
	vec4 spherePos = cyl.getInverseRatationMatrix()*(sph.getPosition()-cyl.getPosition());
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
	//cout<<" if "<< length(plane2.getVelocity()-sph1.getVelocity()) <<" "<< length(plane2.getPosition()-sph1.getPosition())<<"\n";
	if(projectSize(sph1.getVelocity(),plane2.getNormal()) >= 0) return;
	//cout<<"check1\n";
	vec4 spPos = sph1.getPosition();
	float radius = sph1.radius;
	vec4 centerVec = spPos-plane2.getPosition();
	//cout<<centerVec.x<<" "<<centerVec.y<<" "<<centerVec.z<<" "<<centerVec.w<<" = vec\n";
	//cout<<plane2.getNormal().x<<" "<<plane2.getNormal().y<<" "<<plane2.getNormal().z<<" "<<plane2.getNormal().w<<" = base\n";
	float distance = projectSize(centerVec,plane2.getNormal());
	//float distance = dot(centerVec,plane2.getNormal());
	//cout<<"dist = "<<distance<<"\n";
	if(distance<=radius) {
		//cout<<"onCollision";
		colSphere_Plane(sph1,plane2);
	}

}
//not test
void inline checkCollision_SphereSphere(Sphere sph1, Sphere sph2){
	if(projectSize(sph2.getVelocity() - sph1.getVelocity(),sph2.getPosition() - sph1.getPosition()) >= 0) return;
	vec4 sphPos = sph1.getPosition();
	float radius = sph1.radius;
	vec4 d = sphPos - sph2.getPosition();
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
	if(projectSize(cube.getVelocity() - plane.getVelocity(),cube.getPosition() - plane.getPosition()) >= 0) return;
	//vec4 cubeHeight_ModelPlane = projectVec(cube.getPosition() - plane.getPosition(),plane.getNormal());
	float cubeHeight_ModelPlane = projectSize(cube.getPosition()-plane.getPosition(),plane.getNormal());
	if(cubeHeight_ModelPlane >= cube.maxRadius) return;
	else colCube_Plane(cube,plane);
}
//not test
void inline checkCollision_PlaneCylinder(Plane plane,Cylinder cylinder){
	if(projectSize(cylinder.getVelocity() - plane.getVelocity(),cylinder.getPosition() - plane.getPosition()) >= 0) return;
	vec4 dist = cylinder.getPosition()-plane.getPosition();
	vec4 cylinderPosition_PlaneModel = plane.getInverseRatationMatrix()*dist;
	vec4 cylinderNormal_PlaneModel = plane.getInverseRatationMatrix()*cylinder.getRotationMatrix()*vec4(0,1,0,0);
	float height = projectSize(cylinderNormal_PlaneModel,vec4(0,1,0,0)) + length(cross(vec3(0,1,0),vec3(cylinderNormal_PlaneModel))*cylinder.radius);
	if(height<=cylinder.getPosition().y){
		//Collision
		colPlane_Cylinder(plane,cylinder);
	}
}

void inline checkCollision_CubeCube(Cube cube1,Cube cube2){
	if(projectSize(cube2.getVelocity() - cube1.getVelocity(),cube2.getPosition() - cube1.getPosition()) >= 0) return;
}
void inline checkCollision_CubeCylinder(Cube cube1,Cylinder cyl2){
	if(projectSize(cyl2.getVelocity() - cube1.getVelocity(),cyl2.getPosition() - cube1.getPosition()) >= 0) return;
}
void inline checkCollision_CylinderCylinder(Cylinder cylinder1,Cylinder cylinder2){
	if(projectSize(cylinder2.getVelocity() - cylinder1.getVelocity(),cylinder2.getPosition() - cylinder1.getPosition()) >= 0) return;
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


void inline checkCollision(vector<Cube> cu, vector<Cylinder> cy, vector<Plane> pl, vector<Sphere> sp){
	
	for(int i=0;i<sp.size();i++){
		Sphere sp1 = sp.at(i);
		
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
		//cout<<"addPlane\n";
		
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
	Grid(vector<Plane>pl){
		width = 1;
		for(int i=0;i<gridSize;i++)
			for(int j=0;j<gridSize;j++)
				for(int k=0;k<gridSize;k++)
					gridcell[i][j][k] = GridCell();
		//gridcell[i][j][k] = GridCell(begin_x+width*i,begin_y+width*j,begin_z+width*k);
		//hashGrid(cu,cy,sp);
		for(int i=0;i<pl.size();i++) {
			hashPlane(pl[i]);
		}
	};
	void hashGrid(vector<Cube> cu,vector<Cylinder> cy,vector<Sphere> sp){
		for(int i=0;i<cu.size();i++) hashCube(cu[i]);
		for(int i=0;i<cy.size();i++) hashCylinder(cy[i]);
		for(int i=0;i<sp.size();i++) hashSphere(sp[i]);
	}


	void hashCube(Cube r){

		vec4 pos = r.position;
		int a,b,c = 0;
		findIndex(vec3(pos.x,pos.y,pos.z),a,b,c);
		vector<int> x;
		vector<int> y;
		vector<int> z;
		findGrid(vec3(pos.x,pos.y,pos.z),a,b,c,x,y,z);
		for(int i=0;i<x.size();i++){
			gridcell[x[i]][y[i]][z[i]].addCubeToGridCell(r);
		}
	}
	void hashCylinder(Cylinder r){
		vec4 pos = r.position;
		int a,b,c = 0;
		findIndex(vec3(pos.x,pos.y,pos.z),a,b,c);
		vector<int> x;
		vector<int> y;
		vector<int> z;
		findGrid(vec3(pos.x,pos.y,pos.z),a,b,c,x,y,z);
		for(int i=0;i<x.size();i++){
			gridcell[x[i]][y[i]][z[i]].addCylinderToGridCell(r);
		}
	}
	void hashSphere(Sphere r){
		vec4 pos = r.position;
		int a,b,c = 0;
		findIndex(vec3(pos.x,pos.y,pos.z),a,b,c);
		vector<int> x;
		vector<int> y;
		vector<int> z;
		findGrid(vec3(pos.x,pos.y,pos.z),a,b,c,x,y,z);
		for(int i=0;i<x.size();i++){
			gridcell[x[i]][y[i]][z[i]].addSphereToGridCell(r);
		}

	}
	void hashPlane(Plane r){
		vec4 pos = r.position;
		int a,b,c = 0;
		findIndex(vec3(pos.x,pos.y,pos.z),a,b,c);
		//cout<<"posPlane x= "<< pos.x<<" y= "<<pos.y<<" z= "<<pos.z<<"\n";
		//cout<<"index x= "<< a<<" y= "<<b<<" z= "<<c<<"\n";

		for(int i=0;i<gridSize;i++){
			for(int j=0;j<gridSize;j++){
				for(int k=0;k<gridSize;k++){
					/*if(a==0 && b==5 && c==5){
						gridcell[0][j][k].addPlaneToGridCell(r);
					}
					if(a==10 && b==5 && c==5){
						gridcell[10][j][k].addPlaneToGridCell(r);
					}
					if(a==5 && b==5 && c==10){
						gridcell[i][j][10].addPlaneToGridCell(r);
					}
					if(a==5 && b==5 && c==0){
						gridcell[i][j][0].addPlaneToGridCell(r);
					}
					if(a==5 && b==0 && c==5){
						gridcell[i][0][k].addPlaneToGridCell(r);
					}*/
					if(r.orientation==vec3(0,0,0)){}
				}
			}
		}
	}
	void findIndex(vec3 pos, int &i, int &j, int &k){
		i = (int)(pos.x-begin_x)/width;
		j = (int)(pos.y-begin_y)/width;
		k = (int)(pos.z-begin_z)/width;
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

	void findGrid(vec3 pos,int a, int b, int c, vector<int> x, vector<int> y, vector<int> z){
		x.push_back(a); y.push_back(b); z.push_back(c);
		if(pos.x-floor(pos.x)==0.5 && pos.y-floor(pos.y)==0.5 && pos.z-floor(pos.z)==0.5) return;
		
		if(pos.x-floor(pos.x) < 0.5) {										//x<0.5 
			x.push_back(a-1); y.push_back(b); z.push_back(c);
			if(pos.y-floor(pos.y) < 0.5) {									//y<0.5
				x.push_back(a-1); y.push_back(b-1); z.push_back(c);
				if(pos.z-floor(pos.z) < 0.5) {								//z<0.5
					x.push_back(a-1); y.push_back(b-1); z.push_back(c-1); 
				} else {													//z>=0.5
					x.push_back(a-1); y.push_back(b-1); z.push_back(c+1); 
				}
			} else {														//y>=0.5
				x.push_back(a-1); y.push_back(b+1); z.push_back(c); 
				if(pos.z-floor(pos.z) < 0.5) {								//z<0.5
					x.push_back(a-1); y.push_back(b+1); z.push_back(c-1); 
				} else {													//z>=0.5
					x.push_back(a-1); y.push_back(b+1); z.push_back(c+1); 
				}
			}
		} else {															//x>=0.5 
			x.push_back(a+1); y.push_back(b); z.push_back(c); 
			if(pos.y-floor(pos.y) < 0.5) {									//y<0.5 
				x.push_back(a+1); y.push_back(b-1); z.push_back(c); 
				if(pos.z-floor(pos.z) < 0.5) {								//z<0.5
					x.push_back(a+1); y.push_back(b-1); z.push_back(c-1); 
				} else {													//z>=0.5 
					x.push_back(a+1); y.push_back(b-1); z.push_back(c+1); 
				}
			} else {														//y>=0.5
				x.push_back(a+1); y.push_back(b+1); z.push_back(c); 
				if(pos.z-floor(pos.z) < 0.5) {								//z<0.5
					x.push_back(a+1); y.push_back(b+1); z.push_back(c-1); 
				} else {													//z>=0.5 
					x.push_back(a+1); y.push_back(b+1); z.push_back(c+1); 
				}
			}
		}
		
		if(pos.y-floor(pos.y) < 0.5) {										//y<0.5
			x.push_back(a); y.push_back(b-1); z.push_back(c); 
			if(pos.z-floor(pos.z) < 0.5) {									//z<0.5
				x.push_back(a); y.push_back(b-1); z.push_back(c-1); 
			} else {														//z>=0.5
				x.push_back(a); y.push_back(b-1); z.push_back(c+1); 
			}
		} else { 
			x.push_back(a); y.push_back(b+1); z.push_back(c); 
			if(pos.z-floor(pos.z) < 0.5) { 
				x.push_back(a); y.push_back(b+1); z.push_back(c-1); 
			} else { 
				x.push_back(a); y.push_back(b+1); z.push_back(c+1); 
			}
		}
		
		if(pos.z-floor(pos.z) < 0.5) { 
			x.push_back(a); y.push_back(b); z.push_back(c-1); 
			if(pos.x-floor(pos.x) < 0.5) {
				x.push_back(a-1); y.push_back(b); z.push_back(c-1);
			} else {
				x.push_back(a+1); y.push_back(b); z.push_back(c-1);
			}
		} else { 
			x.push_back(a); y.push_back(b); z.push_back(c+1); 
			if(pos.x-floor(pos.x) < 0.5) {
				x.push_back(a-1); y.push_back(b); z.push_back(c+1);
			} else {
				x.push_back(a+1); y.push_back(b); z.push_back(c+1);
			}
		}
		
	}
};
