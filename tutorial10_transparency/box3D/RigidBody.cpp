//header guard at start of header file
#ifndef OBJECT_H
#define OBJECT_H
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GL/glfw.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;
// Include AntTweakBar
#include <AntTweakBar.h>
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
//#include <common/objloader.hpp>
//#include <common/vboindexer.hpp>
//#include <common/quaternion_utils.hpp> // See quaternion_utils.cpp for RotationBetweenVectors, LookAt and RotateTowards
#include <iostream>
#include "Rigidbody.h"
#include "box3DglobalRule.cpp"

using namespace std;

class Rigidbody{

public:
	vec4 position;
	vec4 velocity;
	float mass;

	vec3 orientation;
	vec3 angularVelocity;
	float inertia;
	float size;
	vec4 color;
	float transparent;
	Rigidbody(){
		position = vec4(0,0,0,1);
		mass = 1;

		orientation = vec3(0,0,0);
		angularVelocity = vec3(0,0,0);
		inertia = 1;
		transparent = 0.8;
		size = 1;
		color = vec4(0,0,0,0);
	}
	vec4 getPosition(){
		return position;
	}
	vec4 getVelocity(){
		return velocity;
	}
	void setVelocity(vec4 velo){
		velocity = velo;
	}
	vec3 getMin(){
		return vec3(0,0,0);
	}
	vec3 getMax(){
		return vec3(0,0,0);
	}
	vec3 getSkin(){
		return vec3();
	}
	void addForce(vec4 force,float size){
	}
	void addMomentum(vec4 momentum){
		velocity = velocity+momentum;
	}
	void addAngularMomentum_vec4(vec4 angularMomentum){
		angularVelocity+=vec3(angularMomentum);
	}
	void addAngularMomentum(vec3 angularMomentum){
		angularVelocity+=angularMomentum;
	}
	vec4 getNormal(){
		return normalize(getRotationMatrix()*vec4(0,1,0,0));
	}
	mat4 getRotationMatrix(){
		return eulerAngleYXZ(orientation.y,orientation.x,orientation.z);
	}
	mat4 getInverseRatationMatrix(){
		return eulerAngleYXZ(-orientation.y,-orientation.x,-orientation.z);
	}
	mat4 getTranslationMatrix(){
		return mat4(1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			position.x,position.y,position.z,1.0f);
	}
	void updatePosition(float time){
		position+=(velocity)*time;
		orientation+=angularVelocity*time;
	}
};
void inline printVec4(string name,vec4 vec){
	cout<<name<<"\t: [ "<<vec.x<<"\t"<<vec.y<<"\t"<<vec.z<<"\t"<<vec.w<<" ]\n";
}
//End guard at bottom of header file
#endif 
