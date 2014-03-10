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


#include "Plane.h"
#include <iostream>
using namespace std;
class Plane{
private:
	vec3 position;
	mat4 rotationMatrix;
	vec3 orientation;
	vec3 velocity;
	float inertia;
	float angularVelocity;
	mat4 orientationAxis;
	float size;
	float mass;

	vec3 color;

	float p0[3];
	float p1[3];
	float p2[3];
	float p3[3];
	float p4[3];
	float p5[3];
	float p6[3];
	float p7[3];

	quat quaternionRotation;

	bool gLookAtOther;

public:
	Plane(vec3 planePosition,vec3 planeRotation,vec3 planeVelocity,float planeSize,float planeMass,vec3 planeColor){
		size=planeSize;
		mass=planeMass;
		color=planeColor;
		angularVelocity=1;
		velocity=planeVelocity;
		//อนุรักษ์พลังงานกล ศักย์
		//อนุรักษ์โมเมนตัมเชิงมุม เส้น
		p0[0] = planeVertex0.x*size/2; p0[1] = planeVertex0.y*size/2; p0[2] = planeVertex0.z*size/2;
		p1[0] = planeVertex1.x*size/2; p1[1] = planeVertex1.y*size/2; p1[2] = planeVertex1.z*size/2;
		p2[0] = planeVertex2.x*size/2; p2[1] = planeVertex2.y*size/2; p2[2] = planeVertex2.z*size/2;
		p3[0] = planeVertex3.x*size/2; p3[1] = planeVertex3.y*size/2; p3[2] = planeVertex3.z*size/2;
		orientation=planeRotation;
		rotationMatrix=eulerAngleYXZ(planeRotation.x,planeRotation.y,planeRotation.z);
		position=planePosition;
		gLookAtOther=true;
		quaternionRotation=quat();
	}
	vec3 getPos(){
		return position;
	}
	vec3 getOrientation(){
		return orientation;
	}
	mat4 inline getRotationMatrix(){
		return eulerAngleYXZ(orientation.y,orientation.x,orientation.z);
	}
	mat4 inline getTranslationMatrix(){
		return mat4(1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			position.x,position.y,position.z,1.0f);
	}
	void inline updatePosition(float time){
		position+=velocity*time;
		orientation.x+=0.0001f;
		orientation.y+=0.001f;
		orientation.z+=0.00001f;
	}
	void inline render(){
		glBegin(GL_QUADS);{
			//back
			glColor3f(color.r,color.g,color.b);
			glVertex3fv(p0);
			glVertex3fv(p1);
			glVertex3fv(p3);
			glVertex3fv(p2);
		}glEnd();
	}
};
