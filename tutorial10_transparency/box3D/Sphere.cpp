#include "Sphere.h"
#include "Rigidbody.cpp"
class Sphere : public Rigidbody{
public:
	float radius;
	Sphere(vec3 spherePosition,vec3 sphereRotation,vec3 sphereVelocity,float sphereSize,float sphereMass,vec3 sphereColor){
		radius=sphereSize/2;
		mass=sphereMass;
		color=vec4(sphereColor,0.8f);
		angularVelocity=vec3(0,0,0);
		orientation=sphereRotation;
		position=vec4(spherePosition,1);
		setVelocity(vec4(sphereVelocity,0));
		cout<<"newSphere";
	}
	void inline render(){
		GLUquadric* sphere;
		sphere=gluNewQuadric();
		gluQuadricNormals(sphere,GL_SMOOTH);
		glColor4f(color.r,color.g,color.b,color.a);
		gluSphere(sphere,radius,10,10);
	}
};
