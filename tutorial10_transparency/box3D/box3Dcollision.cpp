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
//not test
void inline checkCollision_SphereCube(Sphere* sph1,Cube* cube2){
	if(projectSize(cube2->velocity - sph1->velocity,cube2->position - sph1->position) >= 0) return;
	//cout<<"check cube\n";
	for (int i = 0; i < 12; i++)
	{
		vec4 start = (cube2->edgeSta[i]);
		vec4 end = (cube2->edgeEnd[i]);
		vec4 colPoint =  dist3D_Segment_to_point(start,end,sph1->position);
		if (length(colPoint)<=sph1->radius){
			cout<<"collision Cube";
			colSphere_Cube(sph1,cube2,colPoint);
			return;
		}
	}
}
//not test
void inline checkCollision_SphereCylinder(Sphere* sph1,Cylinder* cylinder2){
	if(projectSize(cylinder2->getVelocity() - sph1->getVelocity(),cylinder2->getPosition() - sph1->getPosition()) >= 0) return;
	vec4 spherePos = cylinder2->getInverseRatationMatrix()*(sph1->getPosition()-cylinder2->getPosition());
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
	//cout<<"check1\n";
	//cout<<"check\n";
	vec4 spPos = sph1->getPosition();
	float radius = sph1->radius;
	vec4 centerVec = spPos-plane2->getPosition();
	float distance = projectSize(centerVec,plane2->getNormal());
	if(distance<=radius) {
		colSphere_Plane(sph1,plane2);
	}

}
//completed
void inline checkCollision_SphereSphere(Sphere* sph1, Sphere* sph2){
	if(projectSize(sph2->getVelocity() - sph1->getVelocity(),sph2->getPosition() - sph1->getPosition()) >= 0) return;
	vec4 sphPos = sph1->getPosition();
	float radius = sph1->radius;
	vec4 d = sphPos - sph2->getPosition();
	float distance = length(d);
	float sumR = radius + sph2->radius;
	if(distance<=sumR) {
		//onCollision
		colSphere_Sphere(sph1,sph2);
	}
}
//not test
void inline checkCollision_PlaneCube(Plane* plane1,Cube* cube2){
	if(projectSize(cube2->getVelocity() - plane1->getVelocity(),cube2->getPosition() - plane1->getPosition()) >= 0) return;
	//vec4 cubeHeight_ModelPlane* = projectVec(cube2->getPosition() - plane1->getPosition(),plane1->getNormal());
	float cubeHeight_ModelPlane = projectSize(cube2->getPosition()-plane1->getPosition(),plane1->getNormal());
	if(cubeHeight_ModelPlane >= cube2->maxRadius) return;
	else colCube_Plane(cube2,plane1);
}
//not test
void inline checkCollision_PlaneCylinder(Plane* plane1,Cylinder* cylinder2){
	if(projectSize(cylinder2->getVelocity() - plane1->getVelocity(),cylinder2->getPosition() - plane1->getPosition()) >= 0) return;
	vec4 dist = cylinder2->getPosition()-plane1->getPosition();
	vec4 cylinderPosition_PlaneModel = plane1->getInverseRatationMatrix()*dist;
	vec4 cylinderNormal_PlaneModel = plane1->getInverseRatationMatrix()*cylinder2->getRotationMatrix()*vec4(0,1,0,0);
	float height = projectSize(cylinderNormal_PlaneModel,vec4(0,1,0,0)) + length(cross(vec3(0,1,0),vec3(cylinderNormal_PlaneModel))*cylinder2->radius);
	if(height<=cylinder2->getPosition().y){
		//Collision
		colPlane_Cylinder(plane1,cylinder2);
	}
}

void inline checkCollision_CubeCube(Cube* cube1,Cube* cube2){
	if(projectSize(cube2->getVelocity() - cube1->getVelocity(),cube2->getPosition() - cube1->getPosition()) >= 0) return;
}
void inline checkCollision_CubeCylinder(Cube* cube1,Cylinder* cyl2){
	if(projectSize(cyl2->getVelocity() - cube1->getVelocity(),cyl2->getPosition() - cube1->getPosition()) >= 0) return;

}
float f(float t,float r0,float r1,float h1b1Div2, float c1sqr,float a2,float b2){
	float omt = 1-t;
	float tsqr =t*t;
	float omtsqr = omt*omt;
	float term0=r0*sqrt(omtsqr+tsqr);
	float term1=r1*sqrt(omtsqr+c1sqr*tsqr);
	float term2 = h1b1Div2;
	float term3 = abs(omt*a2+t*b2);
	return term0+term1+term2-term3;
}
float fDer(float t,float r0,float r1,float h1b1Div2, float c1sqr,float a2,float b2){
	float omt = 1-t;
	float tsqr =t*t;
	float omtsqr = omt*omt;
	float term0=r0*(2*t-1)/sqrt(omtsqr+tsqr);
	float term1=r1*((1+c1sqr)*t-1)/sqrt(omtsqr+c1sqr*tsqr);
	float term2 = h1b1Div2;
	float term3 = (b2-a2)*sign(omt*a2+t*b2);
	return term0+term1+term2-term3;
}

int separatedByCylinderPerpendiculars1(vec3 p0,vec3 w0, float r0, float h0, vec3 p1,vec3 w1,float r1,float h1){
	vec3 delta = p1-p0;
	float c1 = dot(w0,w1);
	float b1 = sqrt(1-c1*c1);
	vec3 v0 = (w1-c1*w0)/b1;
	vec3 u0 = cross(v0,w0);
	float a2 = dot(delta,u0);
	float b2 = dot(delta,v0);
//	(float t,float r0,float r1,float h1b1Div2, float c1sqr,float a2,float b2)
	if(f(0,r0,r1,h1*b1/2,c1*c1,a2,b2)<=0||f(1,r0,r1,h1*b1/2,c1*c1,a2,b2)<=0) return 1;
	if(fDer(0,r0,r1,h1*b1/2,c1*c1,a2,b2)>=0||fDer(1,r0,r1,h1*b1/2,c1*c1,a2,b2)<=0) return 0;

	float t0,t1,fd0,fd1,tmid,fdmid;
	int i;
	t0=0;
	t1=1;
	tmid = 0.5*(t0+t1);
	if(f(tmid,r0,r1,h1*b1/2,c1*c1,a2,b2)<=0) return 1;
	
	a2=-a2;
	if(f(0,r0,r1,h1*b1/2,c1*c1,a2,b2)<=0 || f(1,r0,r1,h1*b1/2,c1*c1,a2,b2)<=0) return 1;
	if(fDer(0,r0,r1,h1*b1/2,c1*c1,a2,b2)>=0 || fDer(1,r0,r1,h1*b1/2,c1*c1,a2,b2)<=0) return 0;
	
	if(f(tmid,r0,r1,h1*b1/2,c1*c1,a2,b2)<=0) return 1;
	return 1;
}

float g(float s, float t, float r0, float h0Div2, float r1,float h1Div2,
		float a0,float b0,float c0,float a1,float b1,float c1,float lenDelta){
			float omsmt = 1-s-t;
			float ssqr =s*s;
			float tsqr=t*t;
			float omsmtsqr = omsmt*omsmt;
			float temp=ssqr+tsqr+omsmtsqr;
			float L0=a0*s+b0*t+c0*omsmt;
			float L1 = a1*s+b1*t+c1*omsmt;
			float Q0 = temp-L0*L0;
			float Q1=temp-L1*L1;
			return r0*sqrt(Q0)+r1*sqrt(Q1)+h0Div2*abs(L0)+h1Div2*abs(L1)-omsmt*lenDelta;
}
vec2 gDer(float s, float t, float r0, float h0Div2, float r1,float h1Div2,
		float a0,float b0,float c0,float a1,float b1,float c1,float lenDelta){
			float omsmt = 1-s-t;
			float ssqr =s*s;
			float tsqr=t*t;
			float omsmtsqr = omsmt*omsmt;
			float temp=ssqr+tsqr+omsmtsqr;
			float L0=a0*s+b0*t+c0*omsmt;
			float L1 = a1*s+b1*t+c1*omsmt;
			float Q0 = temp-L0*L0;
			float Q1=temp-L1*L1;
			float diffS = s-omsmt, diffT = t-omsmt;
			float diffa0c0 = a0-c0,diffa1c1=a1-c1,diffb0c0=b0-c0,diffb1c1=b1-c1;
			float halfQ0s = diffS-diffa0c0*L0, halfQ1s=diffS-diffa1c1*L1;
			float halfQ0t = diffT-diffa0c0*L0, halfQ1t=diffT-diffa1c1*L1;
			float factor0 = r0/sqrt(Q0),factor1=r1/sqrt(L1);
			float signL0 = sign(L0),signL1=sign(L1);
			vec2 gradient = vec2(0,0);
			gradient[0]+=halfQ0s*factor0;
			gradient[0]+=halfQ1s*factor1;
			gradient[0]+=h0Div2*diffa0c0*signL0;
			gradient[0]+=h1Div2*diffa1c1*signL1;
			gradient[0]+=lenDelta;
			gradient[1]+=halfQ0t*factor0;
			gradient[1]+=halfQ1t*factor1;
			gradient[1]+=h0Div2*diffb0c0*signL0;
			gradient[1]+=h1Div2*diffb1c1*signL1;
			gradient[1]+=lenDelta;
			return gradient;
}
int separatedByOtherDirections(vec3 w0,float r0,float h0,vec3 w1,float r1,float h1,vec3 delta){
	return 1;
}
void inline checkCollision_CylinderCylinder(Cylinder* cy1,Cylinder* cy2){
	/*if(projectSize(cylinder2->getVelocity() - cylinder1->getVelocity(),cylinder2->getPosition() - cylinder1->getPosition()) >= 0) return;
	vec4 minimumDist = dist3D_Segment_to_Segment(cylinder1->getEndPoint1(),cylinder1->getEndPoint2(),cylinder2->getEndPoint1(),cylinder2->getEndPoint2());
	if(length(minimumDist)>= cylinder1->radius + cylinder2->radius) return;
	else if(length(minimumDist) <= cylinder1->radius) colCylinder_Cylinder(cylinder1,cylinder2);
	else{

	}*/
	vec3 c0 = (vec3)cy1->position;
	vec3 c1 = (vec3)cy2->position;
	vec3 w0=(vec3)cy1->getNormal();
	vec3 w1=(vec3)cy2->getNormal();
	float r0 = cy1->radius;
	float r1 = cy2->radius;
	float h0 = cy1->length;
	float h1 = cy2->length;
	vec3 delta = c0 - c1;
	vec3 W0xW1 = cross(w0,w1);
	float lenW0xW1 = length(W0xW1);
	float h0Div2 = h0/2;
	float h1Div2 = h1/2;
	float rSum = r0+r1;
	if(lenW0xW1>0){
		//by w0
		if(r1*lenW0xW1+h0Div2+h1Div2*abs(dot(w0,w1))-abs(dot(w0,delta))) return;
		//by w1
		if(r0*lenW0xW1+h0Div2*abs(dot(w0,w1))+h1Div2-abs(dot(w0,delta))) return;
		//by w0xw1
		if(rSum*lenW0xW1-abs(dot(W0xW1,delta))<0) return;
		if(separatedByCylinderPerpendiculars1(c0,w0,r0,h0,c1,w1,r1,h1)) return;
		if(separatedByCylinderPerpendiculars1(c1,w1,r1,h1,c0,w0,r0,h0)) return;
		if(separatedByOtherDirections(w0,r0,h0,w1,r1,h1,delta)) return;
	} else {
		//by height
		if(h0Div2+h1Div2-abs(dot(w0,delta))<0) return;
		//by radius	
		if(rSum-length((delta-dot(w0,delta)*w0))<0) return;
	}
	colCylinder_Cylinder(cy1,cy2);
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