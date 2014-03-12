#include "Cube.cpp"
#include "Sphere.cpp"
#include "Cylinder.cpp"
#include "Plane.cpp"
#include "Cone.cpp"
#define SMALL_NUM 0.00000001f
#define PARALLEL_SIZE 0.01f
vec4 inline projectVec(vec4 vec,vec4 base){
	return normalize(base)*dot(vec,base)/length(base);
}
float inline projectSize(vec4 vec,vec4 base){
	
	return dot(vec,base)/length(base);
}
bool inline isParallel(vec4 normal1,vec4 normal2){
	if(dot(normal1,normal2)-length(normal1)*length(normal2) <= PARALLEL_SIZE){
	
	}
}

//Sphere
//not test
void inline colSphere_Sphere(Sphere sph1, Sphere sph2){
	vec4 dist = sph2.position-sph1.position;
	vec4 velo1 = sph1.velocity;
	vec4 velo2 = sph2.velocity;
	vec4 relatevelo = velo2-velo1;//ref from sph1
	float lineMomentum = projectSize(relatevelo,normalize(dist));
	sph1.addMomentum(normalize(dist)*lineMomentum);
	sph2.addMomentum(normalize(dist)*-lineMomentum);
	vec3 angularMomentum = cross(vec3(relatevelo),normalize(vec3(dist)));
	sph1.addAngularMomentum_vec4( sph1.getInverseRatationMatrix()*vec4(angularMomentum,0) );
	sph2.addAngularMomentum_vec4( sph2.getInverseRatationMatrix()*vec4(-angularMomentum,0) );
}
//not test
void inline colSphere_Plane(Sphere sph1, Plane plane2){
	vec4 planeNormal = plane2.getNormal();
	vec4 newVelo = projectVec(-sph1.velocity,plane2.getNormal());
	//cout<<sph1.velocity.x<<" "<<sph1.velocity.y<<" "<<sph1.velocity.z<<" "<<sph1.velocity.w<<"\n";
	//cout<<newVelo.x<<" "<<newVelo.y<<" "<<newVelo.z<<" "<<newVelo.w<<"\n";
	sph1.velocity = sph1.velocity + newVelo*2;
	cout<<"col\n";
}
//not test
void inline colSphere_Cube(Sphere sph1, Cube cube2){
	vec4 dist = cube2.position-sph1.position;
	vec4 velo1 = sph1.velocity;
	vec4 velo2 = cube2.velocity;
	vec4 relatevelo = velo2-velo1;//ref from sph1
	float exchangeMomentum = projectSize(relatevelo,normalize(dist));
	sph1.addMomentum(normalize(dist)*exchangeMomentum);
	cube2.addMomentum(normalize(dist)*-exchangeMomentum);
	float newLineEngergy1 = pow(length(sph1.velocity),2);
	float newLineEngergy2 = pow(length(cube2.velocity),2);
	vec3 angularMomentum = cross(vec3(relatevelo),normalize(vec3(dist)));
	sph1.addAngularMomentum(angularMomentum);
	cube2.addAngularMomentum(-angularMomentum);
}
//not test
void inline colSphere_Cylinder(Sphere sph1, Cylinder cy2){
	vec4 dist = cy2.position-sph1.position;
	vec4 velo1 = sph1.velocity;
	vec4 velo2 = cy2.velocity;
	vec4 relatevelo = velo2-velo1;//ref from sph1
	float exchangeMomentum = projectSize(relatevelo,normalize(dist));
	sph1.addMomentum(normalize(dist)*exchangeMomentum);
	cy2.addMomentum(normalize(dist)*-exchangeMomentum);
	float newLineEngergy1 = pow(length(sph1.velocity),2);
	float newLineEngergy2 = pow(length(cy2.velocity),2);
	vec3 angularMomentum = cross(vec3(relatevelo),normalize(vec3(dist)));
	sph1.addAngularMomentum(angularMomentum);
	cy2.addAngularMomentum(-angularMomentum);
}
//void inline colSphere_Cone(Sphere sph1,Cone cone2){
//}

//Cube
void inline colCube_Plane(Cube cube1, Plane plane2){
}
void inline colCube_Cube(Cube cube1, Cube cube2){
}
void inline colCube_Cylinder(Cube cube1, Cylinder cy2){
}
//void inline colCube_Cone(Cube cube1,Cone cone2){
//}

////Cone
//void inline colCone_Sphere(Cone cone1, Sphere sph2){
//}
//void inline colCone_Plane(Cone cone1, Plane plane2){
//}
//void inline colCone_Cube(Cone cone1, Cube cube2){
//}
//void inline colCone_Cylinder(Cone cone1, Cylinder cy2){
//}
//void inline colCone_Cone(Cone cone1,Cone cone2){
//}

//Plane
//void inline colPlane_Plane(Plane plane1, Plane plane2){
//}
void inline colPlane_Cylinder(Plane plane1, Cylinder cy2){
}
//void inline colPlane_Cone(Plane plane1,Cone cone2){
//}

//Cylinder
void inline colCylinder_Cylinder(Cylinder cy1, Cylinder cy2){

}
//void inline colCylinder_Cone(Cylinder cy1,Cone cone2){
//}
// dist3D_Line_to_Line(): get the 3D minimum distance between 2 lines
//    Input:  two 3D lines L1 and L2
//    Return: the shortest distance between L1 and L2

float inline dist3D_Line_to_Line( vec4 l1p1, vec4 l1p0, vec4 l2p1, vec4 l2p0)
{
	vec4   u = l1p1 - l1p0;
	vec4   v = l2p1 - l2p0;
	vec4   w = l1p0 - l2p0;
	float    a = dot(u,u);         // always >= 0
	float    b = dot(u,v);
	float    c = dot(v,v);         // always >= 0
	float    d = dot(u,w);
	float    e = dot(v,w);
	float    D = a*c - b*b;        // always >= 0
	float    sc, tc;

	// compute the line parameters of the two closest points
	if (D < SMALL_NUM) {          // the lines are almost parallel
		sc = 0.0;
		tc = (b>c ? d/b : e/c);    // use the largest denominator
	}
	else {
		sc = (b*e - c*d) / D;
		tc = (a*e - b*d) / D;
	}

	// get the difference of the two closest points
	vec4   dP = w + (sc * u) - (tc * v);  // =  L1(sc) - L2(tc)

	return length(dP);   // return the closest distance
}
//===================================================================
// dist3D_Segment_to_Segment(): get the 3D minimum distance between 2 segments
//    Input:  two 3D line segments S1 and S2
//    Return: the shortest distance between S1 and S2
float inline dist3D_Segment_to_Segment( vec4 s1p1, vec4 s1p0, vec4 s2p1, vec4 s2p0)
{
	vec4   u = s1p1 - s1p0;
	vec4   v = s2p1 - s2p0;
	vec4   w = s1p0 - s2p0;
	float    a = dot(u,u);         // always >= 0
	float    b = dot(u,v);
	float    c = dot(v,v);         // always >= 0
	float    d = dot(u,w);
	float    e = dot(v,w);
	float    D = a*c - b*b;        // always >= 0
	float    sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
	float    tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

	// compute the line parameters of the two closest points
	if (D < SMALL_NUM) { // the lines are almost parallel
		sN = 0.0;         // force using point P0 on segment S1
		sD = 1.0;         // to prevent possible division by 0.0 later
		tN = e;
		tD = c;
	}
	else {                 // get the closest points on the infinite lines
		sN = (b*e - c*d);
		tN = (a*e - b*d);
		if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d < 0.0)
			sN = 0.0;
		else if (-d > a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) < 0.0)
			sN = 0;
		else if ((-d + b) > a)
			sN = sD;
		else {
			sN = (-d +  b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (abs(sN) < SMALL_NUM ? 0.0 : sN / sD);
	tc = (abs(tN) < SMALL_NUM ? 0.0 : tN / tD);

	// get the difference of the two closest points
	vec4   dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

	return length(dP);   // return the closest distance
}
//minimum distance point to disk
float inline dist3D_Dist_to_Point( vec4 diskCenter, float radius, vec4 point){
	//vector1 = vector between disk center and particle;
	vec4 vector1 = point - diskCenter;

	//unitvec1 = unit vector in direction of vec1;
	vec4 unitvec1 = normalize(vector1);

	//vec2 = vector between disk center and point on the perimeter closest to the particle;
	/*vec2 = disk radius * unitvec1, and make z element = 0;
	vec2 = 3 * [0.5774, 0.5774, 0];
	vec2 = [1.7321, 1.7321, 0];

	vec3 = vector between particle and point on the perimeter closest to the particle;
	vec3 = vec1 - vec2;
	vec3 = [3.2679, 3.2679, 5.0000];

	So the min distance is;
	norm(vec3) = 6.8087;
	*/
}
//minimum distance point to line
vec4 inline dist3D_Line_to_point(vec4 line_start, vec4 line_end, vec4 point)
{
	vec4 lineVec = line_end - line_start;
	vec4 pointPos = point - line_start;
	vec4 proj = projectVec(pointPos,lineVec);
	return -pointPos + proj;
}
