// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

//for realtime project
#include "Cylinder.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;
// Include AntTweakBar
#include <AntTweakBar.h>


#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/quaternion_utils.hpp> // See quaternion_utils.cpp for RotationBetweenVectors, LookAt and RotateTowards
using namespace glm;
using namespace std;
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include "box3DglobalRule.cpp"
class Cylinder
{
public:
	vec4 position;
	vec4 velocity;
	float mass;
	
	vec3 orientation;
	vec3 angularVelocity;
	float inertia;

	vec3 color;

	float radius;
	float topRadius;
	float length;
	Cylinder(vec3 cylinderPosition,vec3 cylinderRotation,vec3 cylinderVelocity,float cylinderRadius,float cylinderLength,float cylinderMass,vec3 cylinderColor){
		mass=cylinderMass;
		position=vec4(cylinderPosition,1);
		velocity=vec4(cylinderVelocity,0);
		orientation=cylinderRotation;
		radius=cylinderRadius;
		length=cylinderLength;
		color = cylinderColor;
		velocity = cylinderVelocity;

	}
	vec3 getEndPoint1(){
		return vec3(0,0,0);
	}
	vec3 getEndPoint2(){
		return vec3(0,0,0);
	}
	vec3 inline getMin(){
		return vec3(0,0,0);
	}
	vec3 inline getMax(){
		return vec3(0,0,0);
	}
	vec3 inline getSkin(){
		return vec3();
	}
	void inline addForce(vec3 force,float size){
	}
	void inline addMomentum(vec4 momentum){
		velocity+=momentum;
	}
	void inline addAngularMomentum(vec3 angularMomentum){
		angularVelocity+=angularMomentum;
	}
	vec4 inline getNormal(){
		return normalize(getRotationMatrix()*vec4(0,1,0,0));
	}
	mat4 inline getRotationMatrix(){
		return eulerAngleYXZ(orientation.y,orientation.x,orientation.z);
	}
	mat4 inline getInverseRatationMatrix(){
		return eulerAngleYXZ(-orientation.y,-orientation.x,-orientation.z);
	}
	mat4 inline getTranslationMatrix(){
		return mat4(1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			position.x,position.y,position.z,1.0f);
	}
	void inline updatePosition(float time){
		position+=velocity*time;
		orientation+=angularVelocity*time;
	}
	void render(){
		glColor3f(color.r,color.g,color.b);
		GLUquadric* cyl;
		cyl=gluNewQuadric();
		gluQuadricNormals(cyl,GL_SMOOTH);
		gluCylinder(cyl,radius,topRadius,length,20,1);
	}
};
