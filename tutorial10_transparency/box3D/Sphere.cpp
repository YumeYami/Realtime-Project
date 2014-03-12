#include "Sphere.h"
#include "Rigidbody.cpp"
class Sphere : public Rigidbody{
public:
	float radius;
	Sphere(vec3 spherePosition,vec3 sphereRotation,vec3 sphereVelocity,float sphereSize,float sphereMass,vec3 sphereColor){
		radius=sphereSize/2;
		mass=sphereMass;
		color=sphereColor;
		angularVelocity=vec3(0,0,0);
		orientation=sphereRotation;
		position=vec4(spherePosition,1);
		velocity=(vec4(sphereVelocity,0));
		cout<<"newSphere";
	}
	void inline render(){
		GLUquadric* sphere;
		sphere=gluNewQuadric();
		gluQuadricNormals(sphere,GL_SMOOTH);
		glColor3f(color.r,color.g,color.b);
		gluSphere(sphere,radius,10,10);
	}
};
