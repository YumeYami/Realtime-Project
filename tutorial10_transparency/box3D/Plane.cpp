#include "plane.h"
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
//for realtime project
#include "plane.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <AntTweakBar.h>
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/quaternion_utils.hpp> // See quaternion_utils.cpp for RotationBetweenVectors, LookAt and RotateTowards
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include "box3DglobalRule.cpp"
using namespace glm;
using namespace std;
class Plane
{
public:
	vec3 position;
	vec3 rotation;
	vec3 velocity;
	float momentOfInertia;
	float angularVelocity;
	vec4 quaternionRotation;
	float planeBaseRadius;
	float planeTopRadius;
	float planeLength;
	float mass;
	vec3 color;
	float p0[3];
	float p1[3];
	float p2[3];
	float p3[3];
	Plane(vec3 planePosition,vec3 planeRotation,vec3 planeVelocity,float baseRadius,float topRadius,float length,float m,vec3 c){
		planeBaseRadius =baseRadius;
		planeTopRadius =topRadius;
		planeLength =length;
		velocity=planeVelocity;
		position=planePosition;
		rotation=planeRotation;
		mass=m;
		angularVelocity=1;
		color=c;
		p0[0]=cubeVertex0.x*size; p0[1]=cubeVertex0.y*size; p0[2]=cubeVertex0.z*size;
		p1[0]=cubeVertex1.x*size; p1[1]=cubeVertex1.y*size; p1[2]=cubeVertex1.z*size;
		p2[0]=cubeVertex2.x*size; p2[1]=cubeVertex2.y*size; p2[2]=cubeVertex2.z*size;
		p3[0]=cubeVertex3.x*size; p3[1]=cubeVertex3.y*size; p3[2]=cubeVertex3.z*size;
		//อนุรักษ์พลังงานกล ศักย์
		//อนุรักษ์โมเมนตัมเชิงมุม เส้น
	}
	vec4 inline rotate(vec4 vertex){
		return vec4(0,0,0,0);
	}
	mat4 inline getRotationMatrix(){
		return eulerAngleYXZ(rotation.x,rotation.y,rotation.z);
	}
	mat4 inline getTranslationMatrix(){
		return mat4(1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f, 
			0.0f,0.0f,1.0f,0.0f,
			position.x,position.y,position.z,1.0f);
	}
	void inline render(){
		glColor3f(color.r,color.g,color.b);
		GLUquadric* plane;
		glBegin(GL_QUADS);{
			glVertex3f();
		}glEnd();
	}

};
