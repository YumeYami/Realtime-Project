#include "Cube.h"
#include "Rigidbody.cpp"
class Cube : public Rigidbody{
public:

	float vertex[8][3];
	float p0[3];
	float p1[3];
	float p2[3];
	float p3[3];
	float p4[3];
	float p5[3];
	float p6[3];
	float p7[3];
	Cube(vec3 cubePosition,vec3 cubeRotation,vec3 cubeVelocity,float cubeSize,float cubeMass,vec3 cubeColor) {
		orientation=cubeRotation;
		position=vec4(cubePosition,1);
		velocity=vec4(cubeVelocity,0);
		angularVelocity=vec3(0,0,0);
		size=cubeSize;
		mass=cubeMass;
		color=cubeColor;
		inertia=1;
		//อนุรักษ์พลังงานกล ศักย์
		//อนุรักษ์โมเมนตัมเชิงมุม เส้น
		p0[0] = cubeVertex0.x*size/2; p0[1] = cubeVertex0.y*size/2; p0[2] = cubeVertex0.z*size/2;
		p1[0] = cubeVertex1.x*size/2; p1[1] = cubeVertex1.y*size/2; p1[2] = cubeVertex1.z*size/2;
		p2[0] = cubeVertex2.x*size/2; p2[1] = cubeVertex2.y*size/2; p2[2] = cubeVertex2.z*size/2;
		p3[0] = cubeVertex3.x*size/2; p3[1] = cubeVertex3.y*size/2; p3[2] = cubeVertex3.z*size/2;
		p4[0] = cubeVertex4.x*size/2; p4[1] = cubeVertex4.y*size/2; p4[2] = cubeVertex4.z*size/2;
		p5[0] = cubeVertex5.x*size/2; p5[1] = cubeVertex5.y*size/2; p5[2] = cubeVertex5.z*size/2;
		p6[0] = cubeVertex6.x*size/2; p6[1] = cubeVertex6.y*size/2; p6[2] = cubeVertex6.z*size/2;
		p7[0] = cubeVertex7.x*size/2; p7[1] = cubeVertex7.y*size/2; p7[2] = cubeVertex7.z*size/2;
		
	}
	void inline render(){
		glBegin(GL_QUADS);{
			//back
			//glColor3f(1,1,0);
			glColor3f(color.r,color.g,color.b);
			glVertex3fv(p0);
			glVertex3fv(p1);
			glVertex3fv(p3);
			glVertex3fv(p2);
			//left
			//glColor3f(0,1,0);
			//glColor3f(color.r,color.g,color.b);
			glVertex3fv(p4);
			glVertex3fv(p0);
			glVertex3fv(p2);
			glVertex3fv(p6);
			//right
			//glColor3f(1,0,1);
			//glColor3f(color.r,color.g,color.b);
			glVertex3fv(p5);
			glVertex3fv(p1);
			glVertex3fv(p3);
			glVertex3fv(p7);
			//up
			//glColor3f(1,0,0);
			//glColor3f(color.r,color.g,color.b);
			glVertex3fv(p6);
			glVertex3fv(p7);
			glVertex3fv(p3);
			glVertex3fv(p2);
			//down
			//glColor3f(0,1,1);
			//glColor3f(color.r,color.g,color.b);
			glVertex3fv(p0);
			glVertex3fv(p1);
			glVertex3fv(p5);
			glVertex3fv(p4);


		}glEnd();
	}
};