// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GL/glfw.h>
// Include GLU
#include <GL/GLU.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include "box3Dcollision.h"
#include "box3DglobalRule.h"
#include "Cube.cpp"
#include "Sphere.cpp"
#include "Cylinder.cpp"
#include "Plane.cpp"
#include "Cone.cpp"

//Sphere
//com
void inline colSphere_Sphere(Sphere sph1, Sphere sph2){
	vec4 dist = sph2.position-sph1.position;
	vec4 velo1 = sph1.velocity;
	vec4 velo2 = sph2.velocity;
	vec4 relatevelo = velo2-velo1;//ref from sph1
	float lineMomentum = dot(relatevelo,normalize(dist));
	sph1.addMomentum(normalize(dist)*lineMomentum);
	sph2.addMomentum(normalize(dist)*-lineMomentum);
	float newLineEngergy1 = pow(sph1.velocity.length(),2);
	float newLineEngergy2 = pow(sph2.velocity.length(),2);
	//float angularEnergy = (velo1.length()*velo1.length()+velo2.length()*velo2.length())-(newLineEngergy1+newLineEngergy2);
	vec3 angularMomentum = cross(vec3(relatevelo),normalize(vec3(dist)));
	sph1.addAngularMomentum(angularMomentum);
	sph2.addAngularMomentum(-angularMomentum);
}
void inline colSphere_Plane(Sphere sph1, Plane plane2){
	vec4 planeNormal = plane2.getRotationMatrix()*vec4(0.0f,1.0f,0.0f,0.0f);
	vec4 newVelo = reflect(sph1.velocity,planeNormal);
	sph1.setVelocity(newVelo);
}
void inline colSphere_Cube(Sphere sph1, Cube cube2){
	vec4 dist = cube2.position-sph1.position;
	vec4 velo1 = sph1.velocity;
	vec4 velo2 = cube2.velocity;
	vec4 relatevelo = velo2-velo1;//ref from sph1
	float exchangeMomentum = dot(relatevelo,normalize(dist));
	sph1.addMomentum(normalize(dist)*exchangeMomentum);
	cube2.addMomentum(normalize(dist)*-exchangeMomentum);
	float newLineEngergy1 = pow(sph1.velocity.length(),2);
	float newLineEngergy2 = pow(cube2.velocity.length(),2);
	//float angularEnergy = (velo1.length()*velo1.length()+velo2.length()*velo2.length())-(newLineEngergy1+newLineEngergy2);
	vec3 angularMomentum = cross(vec3(relatevelo),normalize(vec3(dist)));
	sph1.addAngularMomentum(angularMomentum);
	cube2.addAngularMomentum(-angularMomentum);
}
void inline colSphere_Cylinder(Sphere sph1, Cylinder cy2){
	vec4 dist = cy2.position-sph1.position;
	vec4 velo1 = sph1.velocity;
	vec4 velo2 = cy2.velocity;
	vec4 relatevelo = velo2-velo1;//ref from sph1
	float exchangeMomentum = dot(relatevelo,normalize(dist));
	sph1.addMomentum(normalize(dist)*exchangeMomentum);
	cy2.addMomentum(normalize(dist)*-exchangeMomentum);
	float newLineEngergy1 = pow(sph1.velocity.length(),2);
	float newLineEngergy2 = pow(cy2.velocity.length(),2);
	//float angularEnergy = (velo1.length()*velo1.length()+velo2.length()*velo2.length())-(newLineEngergy1+newLineEngergy2);
	vec3 angularMomentum = cross(vec3(relatevelo),normalize(vec3(dist)));
	sph1.addAngularMomentum(angularMomentum);
	cy2.addAngularMomentum(-angularMomentum);
}
void inline colSphere_Cone(Sphere sph1,Cone cone2){
}

//Cube
void inline colCube_Sphere(Cube cube1, Sphere sph2){
	colSphere_Cube(sph2,cube1);
}
void inline colCube_Plane(Cube cube1, Plane plane2){
}
void inline colCube_Cube(Cube cube1, Cube cube2){
}
void inline colCube_Cylinder(Cube cube1, Cylinder cy2){
}
void inline colCube_Cone(Cube cube1,Cone cone2){
}

//Cone
void inline colCone_Sphere(Cone cone1, Sphere sph2){
}
void inline colCone_Plane(Cone cone1, Plane plane2){
}
void inline colCone_Cube(Cone cone1, Cube cube2){
}
void inline colCone_Cylinder(Cone cone1, Cylinder cy2){
}
void inline colCone_Cone(Cone cone1,Cone cone2){
}

//Plane
void inline colPlane_Sphere(Plane plane1, Sphere sph2){
}
void inline colPlane_Plane(Plane plane1, Plane plane2){
}
void inline colPlane_Cube(Plane plane1, Cube cube2){
}
void inline colPlane_Cylinder(Plane plane1, Cylinder cy2){
}
void inline colPlane_Cone(Plane plane1,Cone cone2){
}

//Cylinder
void inline colCylinder_Sphere(Cylinder cy1, Sphere sph2){
}
void inline colCylinder_Plane(Cylinder cy1, Plane plane2){
}
void inline colCylinder_Cube(Cylinder cy1, Cube cu2){
}
void inline colCylinder_Cylinder(Cylinder cy1, Cylinder cy2){
}
void inline colCylinder_Cone(Cylinder cy1,Cone cone2){
}