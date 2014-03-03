// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

//for realtime project
#include "Cube.h"
#include <iostream>
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


using namespace glm;
using namespace std;
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include "box3DglobalRule.cpp"



class Cube{
private:
	vec3 position;
	vec3 rotation;
	vec3 velocity;
	float inertia;
	float angularVelocity;
	vec4 quaternionRotation;
	float size;
	float mass;

	vec3 color;
	bool isRender;
	int begin_indices;
	int begin_indexed_vertices;
	int begin_indexed_uvs;
	int begin_indexed_normals;
	GLfloat p000[3];
	GLfloat p001[3];
	GLfloat p010[3];
	GLfloat p011[3];
	GLfloat p100[3];
	GLfloat p101[3];
	GLfloat p110[3];
	GLfloat p111[3];
public:
	Cube(vec3 cubePosition,vec3 cubeRotation,vec3 cubeVelocity,float cubeSize,float m){
		size=cubeSize;
		velocity=cubeVelocity;
		position=cubePosition;
		rotation=cubeRotation;
		mass=m;
		angularVelocity=1;
		//อนุรักษ์พลังงานกล ศักย์
		//อนุรักษ์โมเมนตัมเชิงมุม เส้น
		isRender=false;
		p000[0]=cubeVertex000.x*size; p000[1]=cubeVertex000.y*size; p000[2]=cubeVertex000.z*size;
		p001[0]=cubeVertex001.x*size; p001[1]=cubeVertex001.y*size; p001[2]=cubeVertex001.z*size;
		p010[0]=cubeVertex010.x*size; p010[1]=cubeVertex010.y*size; p010[2]=cubeVertex010.z*size;
		p011[0]=cubeVertex011.x*size; p011[1]=cubeVertex011.y*size; p011[2]=cubeVertex011.z*size;
		p100[0]=cubeVertex100.x*size; p100[1]=cubeVertex100.y*size; p100[2]=cubeVertex100.z*size;
		p101[0]=cubeVertex101.x*size; p101[1]=cubeVertex101.y*size; p101[2]=cubeVertex101.z*size;
		p110[0]=cubeVertex110.x*size; p110[1]=cubeVertex110.y*size; p110[2]=cubeVertex110.z*size;
		p111[0]=cubeVertex111.x*size; p111[1]=cubeVertex111.y*size; p111[2]=cubeVertex111.z*size;
	}
	void addForce(vec3 force,float size){
	}
	vec4 rotate(vec4 vertex){
		return vec4(0,0,0,0);
	}
	mat4 getRotationMatrix(){
		//cout<<rotation.x<<" "<<rotation.y<<" "<<rotation.z<<endl;
		return eulerAngleYXZ(rotation.x,rotation.y,rotation.z);
	}
	mat4 getTranslationMatrix(){
		return mat4(1,0,0,position.x, 0,1,0,position.y, 0,0,1,position.z, 0,0,0,1);
	}
	mat4 getScaleMatrix(){
		return mat4(1);
	}
	void renderCube(vec3 color){
		//rotation.x+=0.1f;
		//rotation.y+=0.1f;
		//rotation.z+=0.1f;
		glBegin(GL_QUADS);{
			//front
			glColor3f(0,0,1);
			glVertex3f(p100[0],p100[1],p100[2]);
			glVertex3f(p101[0],p101[1],p101[2]);
			glVertex3f(p111[0],p111[1],p111[2]);
			glVertex3f(p110[0],p110[1],p110[2]);
			glVertex3fv(p100);
			glVertex3fv(p101);
			glVertex3fv(p111);
			glVertex3fv(p110);
			//back
			glColor3f(1,1,0);
			glVertex3fv(p000);
			glVertex3fv(p001);
			glVertex3fv(p011);
			glVertex3fv(p010);
			//leaf
			glColor3f(0,1,0);
			glVertex3fv(p000);
			glVertex3fv(p010);
			glVertex3fv(p110);
			glVertex3fv(p100);
			//right
			glColor3f(1,0,1);
			glVertex3fv(p101);
			glVertex3fv(p001);
			glVertex3fv(p011);
			glVertex3fv(p111);
			//up
			glColor3f(1,0,0);
			glVertex3fv(p010);
			glVertex3fv(p011);
			glVertex3fv(p111);
			glVertex3fv(p110);
			//down
			glColor3f(0,1,1);
			glVertex3fv(p000);
			glVertex3fv(p001);
			glVertex3fv(p101);
			glVertex3fv(p100);
		}glEnd();
	}
};