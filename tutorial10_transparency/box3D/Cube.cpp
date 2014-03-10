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
		p000=rotate(cubeVertex000*size/2);
		p001=rotate(cubeVertex001*size/2);
		p010=rotate(cubeVertex010*size/2);
		p011=rotate(cubeVertex011*size/2);
		p100=rotate(cubeVertex100*size/2);
		p101=rotate(cubeVertex101*size/2);
		p110=rotate(cubeVertex110*size/2);
		p111=rotate(cubeVertex111*size/2);
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
	mat4 getScaleMatrix(){
		return mat4();
	}
	void updatePosition(float time){
		
	}
	void renderCube(vec3 color){
		glBegin(GL_QUADS);{
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
		}glEnd();
	}
	void derenderCube(std::vector<unsigned short> indices,
		std::vector<glm::vec3> indexed_vertices,
		std::vector<glm::vec2> indexed_uvs,
		std::vector<glm::vec3> indexed_normals){

	}
};