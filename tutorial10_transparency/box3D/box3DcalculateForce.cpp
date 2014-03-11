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
void inline colSphere_Sphere(Sphere sph1, Sphere sph2){
	vec3 velo1 = sph1.getVelocity();
	sph1.setVelocity(sph2.getVelocity());
	sph2.setVelocity(velo1);
}
void inline colSphere_Plane(Sphere sph1, Plane plane2){
	vec4 planeNormal = plane2.getRotationMatrix()*vec4(0.0f,1.0f,0.0f,0.0f);
	vec3 newVelo = reflect(sph1.getVelocity(),vec3(planeNormal));
	sph1.setVelocity(newVelo);
}
void inline colSphere_Cube(Sphere sph1, Cube cube2,vec3 pointCollisionModelCube){
	
	
}
void inline colSphere_Cylinder(Sphere sph1, Cylinder cy2){
}
void inline colSphere_Cone(Sphere sph1,Cone cone2){
}

//Cube
void inline colCube_Sphere(Cube cube1, Cube sph2){
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
	colSphere_Cylinder(sph2,cy1);
}
void inline colCylinder_Plane(Cylinder cy1, Plane plane2){
	colPlane_Cylinder(plane2,cy1);
}
void inline colCylinder_Cube(Cylinder cy1, Cube cu2){
	colCube_Cylinder(cu2,cy1);
}
void inline colCylinder_Cylinder(Cylinder cy1, Cylinder cy2){
}
void inline colCylinder_Cone(Cylinder cy1,Cone cone2){
	colCone_Cylinder(cone2,cy1);
}