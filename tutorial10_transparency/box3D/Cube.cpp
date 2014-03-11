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


#include "Cube.h"
#include <iostream>
using namespace std;
class Cube{
public:
	vec3 position;
	vec3 velocity;
	float mass;
	
	vec3 orientation;
	vec3 angularVelocity;
	float inertia;

	float size;
	vec3 color;

	float vertex[8][3];
	float p0[3];
	float p1[3];
	float p2[3];
	float p3[3];
	float p4[3];
	float p5[3];
	float p6[3];
	float p7[3];
	Cube(vec3 cubePosition,vec3 cubeRotation,vec3 cubeVelocity,float cubeSize,float cubeMass,vec3 cubeColor){
		orientation=cubeRotation;
		position=cubePosition;
		velocity=cubeVelocity;
		angularVelocity=vec3(0,0,0);
		size=cubeSize;
		mass=cubeMass;
		color=cubeColor;
		inertia=1;
		//อนุรักษ์พลังงานกล ศักย์
		//อนุรักษ์โมเมนตัมเชิงมุม เส้น
		p0[0] = cubeVertex0.x*size/2; p0[1] = cubeVertex0.y*size/2; p0[2] = cubeVertex0.z*size/2;
		p1[0] = cubeVertex1.x*size/2; p1[1] = cubeVertex1.y*size/2; p1[2] = cubeVertex1.z*size/2;
		p2[0] = cubeVertex2.x*size/2; p2[1] = cubeVertex2.y*size/2; p2[2] = cubeVertex2.z*size/2;
		p3[0] = cubeVertex3.x*size/2; p3[1] = cubeVertex3.y*size/2; p3[2] = cubeVertex3.z*size/2;
		p4[0] = cubeVertex4.x*size/2; p4[1] = cubeVertex4.y*size/2; p4[2] = cubeVertex4.z*size/2;
		p5[0] = cubeVertex5.x*size/2; p5[1] = cubeVertex5.y*size/2; p5[2] = cubeVertex5.z*size/2;
		p6[0] = cubeVertex6.x*size/2; p6[1] = cubeVertex6.y*size/2; p6[2] = cubeVertex6.z*size/2;
		p7[0] = cubeVertex7.x*size/2; p7[1] = cubeVertex7.y*size/2; p7[2] = cubeVertex7.z*size/2;
		
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
	void inline addMomentum(vec3 momentum){
		velocity+=momentum;
	}
	void inline addAngularMomentum(vec3 angularMomentum){
		angularVelocity+=angularMomentum;
	}
	vec3 inline getNormal(){
		return vec3(getRotationMatrix()*vec4(0,1,0,1));
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
	void inline render(){
		glBegin(GL_QUADS);{
			//back
			glColor3f(1,1,0);
			glVertex3fv(p0);
			glVertex3fv(p1);
			glVertex3fv(p3);
			glVertex3fv(p2);
			//left
			glColor3f(0,1,0);
			glVertex3fv(p4);
			glVertex3fv(p0);
			glVertex3fv(p2);
			glVertex3fv(p6);
			//right
			glColor3f(1,0,1);
			glVertex3fv(p5);
			glVertex3fv(p1);
			glVertex3fv(p3);
			glVertex3fv(p7);
			//up
			glColor3f(1,0,0);
			glVertex3fv(p6);
			glVertex3fv(p7);
			glVertex3fv(p3);
			glVertex3fv(p2);
			//down
			glColor3f(0,1,1);
			glVertex3fv(p0);
			glVertex3fv(p1);
			glVertex3fv(p5);
			glVertex3fv(p4);
		}glEnd();
	}
};