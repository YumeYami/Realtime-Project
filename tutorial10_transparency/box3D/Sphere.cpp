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
	vec3 position;
	vec3 rotation;
	vec3 velocity;
	float momentOfInertia;
	float angularVelocity;
	vec4 quaternionRotation;
	float size;
	float mass;
	vec3 color;
	Sphere(vec3 spherePosition,vec3 sphereRotation,vec3 sphereVelocity,float sphereSize,float m,vec3 c){
		size=sphereSize;
		velocity=sphereVelocity;
		position=spherePosition;
		rotation=sphereRotation;
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
		GLUquadric* sphere;
		sphere=gluNewQuadric();
		gluQuadricNormals(sphere, GL_SMOOTH);
		gluSphere(sphere,0.2,10,10);
	}
};
