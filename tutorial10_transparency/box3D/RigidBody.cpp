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

#include "Rigidbody.h"
#include "box3DglobalRule.cpp"
#include <iostream>
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
	vec3 color;

	Rigidbody(){
		position = vec4(0,0,0,1);
		velocity = vec4(0,0,0,0);
		mass = 1;

		orientation = vec3(0,0,0);
		angularVelocity = vec3(0,0,0);
		inertia = 1;

		size = 1;
		color = vec3(0,0,0);
	}
	void inline setVelocity(vec4 newvelo){
		velocity=newvelo;
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
	void inline addForce(vec4 force,float size){
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
};
//End guard at bottom of header file
#endif 
