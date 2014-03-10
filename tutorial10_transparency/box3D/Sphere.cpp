// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

//for realtime project
#include "Sphere.h"
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
class Sphere
{
public:
private:
	vec3 position;
	vec3 rotation;
	mat4 rotationMatrix;
	vec3 velocity;
	float inertia;
	float angularVelocity;
	quat quaternionRotation;
	float size;
	float mass;

	vec3 color;
public:
	Sphere(vec3 spherePosition,vec3 sphereRotation,vec3 sphereVelocity,float sphereSize,float sphereMass,vec3 sphereColor){
		size=sphereSize;
		mass=sphereMass;
		color=sphereColor;
		angularVelocity=1;
		//อนุรักษ์พลังงานกล ศักย์
		//อนุรักษ์โมเมนตัมเชิงมุม เส้น
		rotation=sphereRotation;
		position=spherePosition;
	}
	void inline addForce(vec3 force,float size){
	}
	vec4 inline rotate(vec4 vertex){/*
							 glTranslatef(xPos - scroll_x,yPos - scroll_y,0);			
							 glRotatef(angle,0.0f,0.0f,1.0f);*/
		return vec4(0,0,0,0);
	}
	mat4 inline getRotationMatrix(){
		return eulerAngleYXZ(rotation.y,rotation.x,rotation.z);
	}
	mat4 inline getTranslationMatrix(){
		return mat4(1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			position.x,position.y,position.z,1.0f);
	}
	void inline updatePosition(float time){
		position+=velocity*time;
		rotation.x+=0.0001f;
		rotation.y+=0.001f;
		rotation.z+=0.00001f;
	}
	void inline render(){
		GLUquadric* sphere;
		sphere=gluNewQuadric();
		gluQuadricNormals(sphere,GL_SMOOTH);
		glColor3f(color.r,color.g,color.b);
		gluSphere(sphere,size,10,10);
	}
};
