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
	vec3 velocity;
	float mass;
	
	vec3 orientation;
	vec3 angularVelocity;
	float inertia;

	float size;
	vec3 color;

public:
	Sphere(vec3 spherePosition,vec3 sphereRotation,vec3 sphereVelocity,float sphereSize,float sphereMass,vec3 sphereColor){
		size=sphereSize/2;
		mass=sphereMass;
		color=sphereColor;
		angularVelocity=vec3(0,0,0);
		orientation=sphereRotation;
		position=spherePosition;
	}
	float inline getRadius(){
		return size;
	}
	vec3 inline getPos(){
		return position;
	}
	vec3 inline getVelocity(){
		return velocity;
	}
	void inline setVelocity(vec3 newvelo){
		velocity=newvelo;
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
	vec3 inline getNormal(){
		return vec3();
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
		GLUquadric* sphere;
		sphere=gluNewQuadric();
		gluQuadricNormals(sphere,GL_SMOOTH);
		glColor3f(color.r,color.g,color.b);
		gluSphere(sphere,size,10,10);
	}
};
