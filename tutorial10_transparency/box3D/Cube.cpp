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
	vec4 p000;
	vec4 p001;
	vec4 p010;
	vec4 p011;
	vec4 p100;
	vec4 p101;
	vec4 p110;
	vec4 p111;
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
		p000=rotate(vertex000);
		p001=rotate(vertex001);
		p010=rotate(vertex010);
		p011=rotate(vertex011);
		p100=rotate(vertex100);
		p101=rotate(vertex101);
		p110=rotate(vertex110);
		p111=rotate(vertex111);
	}
	void addForce(vec3 force,float size){
	}
	vec4 rotate(vec4 vertex){/*
							 glTranslatef(xPos - scroll_x,yPos - scroll_y,0);			
							 glRotatef(angle,0.0f,0.0f,1.0f);*/
		return vec4(0,0,0,0);
	}
	mat4 getRotationMatrix(){
		return eulerAngleYXZ(rotation.x,rotation.y,rotation.z);
	}
	mat4 getTranslationMatrix(){
		return mat4();
	}
	void renderCube(vec3 color){
		glBegin(GL_QUADS);{
			//vec4 p000=vec4(-size/2,-size/2,-size/2,0);
			//float* tp000=eulerAngleYXZ(rotation.x,rotation.y,rotation.z)*p000;
			//float* pos;
			//indexed_rotates.push_back(mat4(2,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1));
			//glRotatef(angularVelocity*0.1,rotation.x,rotation.y,rotation.z);
			//front
			glPushMatrix();
			//glRotatef(1.0,1.0f,1.0f,1.0f);
			//indexed_rotates.push_back(mat4(1.0f,0,0,0, 0,1.0f,0,0, 0,0,1.0f,0, 0,0,0,1.0f));
			glColor3f(0,0,1);
			glVertex3f(position.x-size/2,position.y-size/2,position.z+size/2);
			glVertex3f(position.x+size/2,position.y-size/2,position.z+size/2);
			glVertex3f(position.x+size/2,position.y+size/2,position.z+size/2);
			glVertex3f(position.x-size/2,position.y+size/2,position.z+size/2);
			//back
			glColor3f(1,1,0);
			glVertex3f(position.x-size/2,position.y-size/2,position.z-size/2);
			glVertex3f(position.x+size/2,position.y-size/2,position.z-size/2);
			glVertex3f(position.x+size/2,position.y+size/2,position.z-size/2);
			glVertex3f(position.x-size/2,position.y+size/2,position.z-size/2);
			//leaf
			glColor3f(0,1,0);
			glVertex3f(position.x+size/2,position.y-size/2,position.z-size/2);
			glVertex3f(position.x+size/2,position.y+size/2,position.z-size/2);
			glVertex3f(position.x+size/2,position.y+size/2,position.z+size/2);
			glVertex3f(position.x+size/2,position.y-size/2,position.z+size/2);
			//right
			glColor3f(1,0,1);
			glVertex3f(position.x-size/2,position.y-size/2,position.z-size/2);
			glVertex3f(position.x-size/2,position.y+size/2,position.z-size/2);
			glVertex3f(position.x-size/2,position.y+size/2,position.z+size/2);
			glVertex3f(position.x-size/2,position.y-size/2,position.z+size/2);
			//up
			glColor3f(1,0,0);
			glVertex3f(position.x-size/2,position.y+size/2,position.z-size/2);
			glVertex3f(position.x+size/2,position.y+size/2,position.z-size/2);
			glVertex3f(position.x+size/2,position.y+size/2,position.z+size/2);
			glVertex3f(position.x-size/2,position.y+size/2,position.z+size/2);
			//down
			glColor3f(0,1,1);
			glVertex3f(position.x-size/2,position.y-size/2,position.z-size/2);
			glVertex3f(position.x+size/2,position.y-size/2,position.z-size/2);
			glVertex3f(position.x+size/2,position.y-size/2,position.z+size/2);
			glVertex3f(position.x-size/2,position.y-size/2,position.z+size/2);
			glPopMatrix();
		}glEnd();
	}
	void derenderCube(std::vector<unsigned short> indices,
		std::vector<glm::vec3> indexed_vertices,
		std::vector<glm::vec2> indexed_uvs,
		std::vector<glm::vec3> indexed_normals){

	}
};