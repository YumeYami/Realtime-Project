#include "Cylinder.h"
#include "Rigidbody.cpp"
class Cylinder : public Rigidbody {
public:
	float radius;
	float length;
	Cylinder(vec3 cylinderPosition,vec3 cylinderRotation,vec3 cylinderVelocity,float cylinderRadius,float cylinderLength,float cylinderMass,vec3 cylinderColor){
		mass=cylinderMass;
		position=vec4(cylinderPosition,1);
		velocity=(vec4(cylinderVelocity,0));
		orientation=cylinderRotation;
		radius=cylinderRadius;
		length=cylinderLength;
		color = vec4(cylinderColor,0.8f);

	}
	vec4 inline getPositionCylinder(){
		return position + (getNormal()*length/2);
	}
	vec4 inline getBasePoint(){
		return position;
	}
	vec4 inline getTopPoint(){
		return position + (getNormal()*length);
	}
	void inline render(){
		glColor4f(color.r,color.g,color.b,color.a);
		GLUquadric* cyl;
		cyl=gluNewQuadric();
		gluQuadricNormals(cyl,GL_SMOOTH);
		gluCylinder(cyl,radius,radius,length,20,1);
	}
};