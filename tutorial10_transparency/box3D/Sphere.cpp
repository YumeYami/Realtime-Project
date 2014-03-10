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
	mat4 rotation;
	vec3 velocity;
	float inertia;
	float angularVelocity;
	quat quaternionRotation;
	float size;
	float mass;

	vec3 color;
public:
	Sphere(vec3 spherePosition,vec3 sphereRotation,vec3 sphereVelocity,float sphereSize,float m){
		size=sphereSize;
		mass=m;
		angularVelocity=1;
		//อนุรักษ์พลังงานกล ศักย์
		//อนุรักษ์โมเมนตัมเชิงมุม เส้น
		rotation=eulerAngleYXZ(sphereRotation.x,sphereRotation.y,sphereRotation.z);
		position=spherePosition;
	}
	void addForce(vec3 force,float size){
	}
	vec4 rotate(vec4 vertex){/*
							 glTranslatef(xPos - scroll_x,yPos - scroll_y,0);			
							 glRotatef(angle,0.0f,0.0f,1.0f);*/
		return vec4(0,0,0,0);
	}
	mat4 getRotationMatrix(){
		return rotation;
	}
	mat4 getTranslationMatrix(){
		return mat4(1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			position.x,position.y,position.z,1.0f);
	}
	mat4 getScaleMatrix(){
		return mat4(1.0f);
	}
	void updatePosition(float time){
		position+=velocity*time;
		rotation;
		vec3 desiredDir = vec3(1.0f);
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f); // +Y

		// Compute the desired orientation
		quat targetOrientation = normalize(LookAt(desiredDir, desiredUp));

		// And interpolate
		quaternionRotation = RotateTowards(quaternionRotation, targetOrientation, time);

		glm::mat4 RotationMatrix = mat4_cast(quaternionRotation);
	}
	void renderSphere(vec3 color){
		glColor3f(color.r,color.g,color.b);
		GLUquadric* sphere;
		sphere=gluNewQuadric();
		gluQuadricNormals(gluNewQuadric(),GL_SMOOTH);
	}
	void derenderSphere(std::vector<unsigned short> indices,
		std::vector<glm::vec3> indexed_vertices,
		std::vector<glm::vec2> indexed_uvs,
		std::vector<glm::vec3> indexed_normals){

	}
};
