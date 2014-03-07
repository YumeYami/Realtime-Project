#include "Cylinder.h"
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
//for realtime project
#include "cylinder.h"
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
class Cylinder
{
public:
	vec3 position;
	vec3 rotation;
	vec3 velocity;
	float momentOfInertia;
	float angularVelocity;
	vec4 quaternionRotation;
	float cylinderBaseRadius;
	float cylinderTopRadius;
	float cylinderLength;
	float mass;
	vec3 color;
	Cylinder(vec3 cylinderPosition,vec3 cylinderRotation,vec3 cylinderVelocity,float baseRadius,float topRadius,float length,float m,vec3 c){
		cylinderBaseRadius =baseRadius;
		cylinderTopRadius =topRadius;
		cylinderLength =length;
		velocity=cylinderVelocity;
		position=cylinderPosition;
		rotation=cylinderRotation;
		mass=m;
		angularVelocity=1;
		color=c;
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
		GLUquadric* cylinder;
		cylinder=gluNewQuadric();
		gluQuadricNormals(cylinder, GL_SMOOTH);
		gluCylinder(gluNewQuadric(),cylinderBaseRadius,cylinderTopRadius,cylinderLength,20,2);
	}

};
