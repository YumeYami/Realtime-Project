// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
//Realtime-Project library
#include "box3D/box3Dcollision.cpp"
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GL/glfw.h>
// Include GLU
#include <GL/GLU.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>


std::vector<unsigned short> indices;
std::vector<glm::vec3> indexed_vertices;
std::vector<glm::mat4> indexed_rotates;
std::vector<glm::vec2> indexed_uvs;
std::vector<glm::vec3> indexed_normals;

vector<Cube*> c3;
vector<Sphere*> sphere;
vector<Cylinder*> cylinder;
vector<Plane*> plane;

Grid grid;

void addSphere(){
	vec3 position = vec3(rand()%(gridSize-4)-4,begin_x+gridSize-4,rand()%(gridSize-4)-4);
	vec3 rotation = vec3(0,0,1);
	vec3 velocity = vec3(rand()%2/10.0,-rand()%2/10.0,rand()%2/10.0);
	float size = rand()%6/10.0+0.5;
	float mass = 1;
	vec3 color = vec3(rand()%11/10.0,rand()%11/10.0,rand()%11/10.0);
	Sphere* sp = new Sphere(position,rotation,velocity,size,mass,color);
	sphere.push_back(sp);
}
void addCube(){
	vec3 position = vec3(rand()%(gridSize-4)-4,begin_x+gridSize-4,rand()%(gridSize-4)-4);
	vec3 rotation = vec3(0,0,1);
	vec3 velocity = vec3(rand()%2/10.0,-rand()%2/10.0,rand()%2/10.0);
	float size = 1;
	float mass = 1;
	vec3 color = vec3(rand()%11/10.0,rand()%11/10.0,rand()%11/10.0);
	Cube *cube=new Cube(position,rotation,velocity,size,mass,color);
	c3.push_back(cube);
}
void addCylinder(){
	vec3 position = vec3(rand()%(gridSize-4)-4,begin_x+gridSize-4,rand()%(gridSize-4)-4);
	vec3 rotation = vec3(0,0,1);
	vec3 velocity = vec3(rand()%2/10.0,-rand()%2/10.0,rand()%2/10.0);
	float radius = 0.5;
	float length = 1;
	float mass = 1;
	vec3 color = vec3(rand()%11/10.0,rand()%11/10.0,rand()%11/10.0);
	Cylinder *cy = new Cylinder(position,rotation,velocity,radius,length,mass,color);
	cylinder.push_back(cy);
}
void addPlane(){
	//top,bottom,left,right,back,front
	vec3 pos[6] = {vec3(1.5,begin_y+gridSize-1.5,1.5), vec3(1.5,begin_y+1.5,1.5),vec3(begin_x+1.5,1.5,1.5),
		vec3(begin_x+gridSize-1.5,1.5,1.5),vec3(1.5,1.5,begin_z+gridSize-1.5),vec3(1.5,1.5,begin_z+1.5)};
	vec3 rot[6] = {vec3(PI,0,0), vec3(0,0,0),vec3(0,0,-PI/2),vec3(0,0,PI/2),vec3(-PI/2,0,0),vec3(PI/2,0,0)};
	for(int i=0;i<6;i++){
		vec3 position = pos[i];
		vec3 rotation = rot[i];
		vec3 velocity = vec3(0,0,0);
		float size = 20;
		float mass = 1;
		vec3 color = vec3(rand()%11/10.0,rand()%11/10.0,rand()%11/10.0);
		Plane *pl=new Plane(position,rotation,velocity,size,mass,color);
		plane.push_back(pl);
	}
}
void tranparentPlane(){
	for(int i=0;i<5;i++){
		//plane.pop_back();
	}
}

int lastKey1=GLFW_RELEASE;
int lastKey2=GLFW_RELEASE;
int lastKey3=GLFW_RELEASE;
int lastKey4=GLFW_RELEASE;
int lastMouse=GLFW_RELEASE;
int fixX=0,fixY=0;
int showX=0,showY=0;
int clickX1,clickY1=0;
int clickX2,clickY2=0;
int xposL,yposL;

void onPress(){
	//sphere
	if (glfwGetKey('1') == GLFW_PRESS){
		if(lastKey1 == GLFW_RELEASE) {
			addSphere();
		}
		lastKey1 = GLFW_PRESS;

	}
	else if (glfwGetKey('1') == GLFW_RELEASE){
		lastKey1 = GLFW_RELEASE;
	}

	//cube
	if (glfwGetKey('2') == GLFW_PRESS){
		if(lastKey2 == GLFW_RELEASE) addCube();
		lastKey2 = GLFW_PRESS;
	}
	else if (glfwGetKey('2') == GLFW_RELEASE){
		lastKey2 = GLFW_RELEASE;
	}

	//cylinder
	if (glfwGetKey('3') == GLFW_PRESS){
		if(lastKey3 == GLFW_RELEASE) addCylinder();
		lastKey3 = GLFW_PRESS;
	}
	else if (glfwGetKey('3') == GLFW_RELEASE){
		lastKey3 = GLFW_RELEASE;
	}

	//plane
	if (glfwGetKey('4') == GLFW_PRESS){
		if(lastKey4 == GLFW_RELEASE) 
			if(plane.size()==0)addPlane();
			else tranparentPlane();
			lastKey4 = GLFW_PRESS;
	}
	else if (glfwGetKey('4') == GLFW_RELEASE){
		lastKey4 = GLFW_RELEASE;
	}

	if( lastMouse==GLFW_RELEASE && glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS){
		glfwGetMousePos(&clickX1,&clickY1);
		lastMouse=GLFW_PRESS;
	} else if(lastMouse==GLFW_PRESS && glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS) {
		glfwGetMousePos(&clickX2,&clickY2);
		float dx = clickX2-clickX1;
		float dy = clickY2-clickY1;
		//cout<<"x = "<<dx;
		//cout<<"y = "<<dy<<"\n";
		clickX1=clickX2;
		clickY1=clickY2;
		dx/=100.0f;
		dy/=-100.0f;
		//top,bottom,left,right,back,front
		float topPos = plane[0]->position.y;
		float btmPos = plane[1]->position.y;
		float lftPos = plane[2]->position.x;
		float rhtPos = plane[3]->position.x;
		//float bckPos = plane[4]->position.z;
		//float fntPos = plane[5]->position.z;
		vec4 pos = vec4(0,0,0,0);
		if(topPos+dy<=begin_y+gridSize && btmPos+dy>begin_y) pos.y=dy;
		if(lftPos+dx>=begin_x && rhtPos+dx<begin_x+gridSize) pos.x=dx;
		grid.clearGridPlane();
		for(int i=0;i<plane.size();i++) {
			plane[i]->position+=pos;
			grid.hashPlane(plane[i]);
		}

	} else if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)==GLFW_RELEASE) {
		lastMouse=GLFW_RELEASE;
	}

}

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
	GLUTkeyboardfun(keyboard);
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}


	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle( "Tutorial 10" );
	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );
	glfwSetMousePos(1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE); // Not this time !

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardTransparentShading.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
	GLuint ScaleMatrixID = glGetUniformLocation(programID, "Scale");
	GLuint TranslateMatrixID = glGetUniformLocation(programID, "Translate");
	GLuint RotateMatrixID = glGetUniformLocation(programID, "Rotate");
	// Get a handle for our buffers
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	GLuint vertexRotation_modelspaceID = glGetAttribLocation(programID, "vertexRotation_modelspace");
	GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
	GLuint vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

	// Load the texture
	GLuint Texture = loadDDS("uvmap.DDS");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	//---------------------------------------------------------------------------------------------------------------


	/*Cube cube1= Cube(vec3(1,1,1),vec3(0,0,1),vec3(1,0,0),1,1,vec3(0.5f,0.2f,0.3f));
	Cube cube2= Cube(vec3(0,1,0),vec3(0,2.5f,1),vec3(0,1,0),0.5f,1,vec3(0.5f,0.2f,0.3f));
	Cube cube3= Cube(vec3(1,0,0),vec3(1,0,1),vec3(0,0,1),0.2f,1,vec3(0.5f,0.2f,0.3f));
	c3.push_back(&cube1);
	c3.push_back(&cube2);
	c3.push_back(&cube3);

	Sphere sphere1= Sphere(vec3(1,1,1),vec3(0,0,1),vec3(0,0,0),1,1,vec3(0.5f,0.2f,0.3f));
	Sphere sphere2= Sphere(vec3(0,1,0),vec3(0,2.5f,1),vec3(0,0,0),0.5f,1,vec3(0.0f,0.4f,0.3f));
	Sphere sphere3= Sphere(vec3(1,0,0),vec3(1,0,1),vec3(0,0,0),0.2f,1,vec3(0.1f,0.2f,0.8f));
	sphere.push_back(&sphere1);
	sphere.push_back(&sphere2);
	sphere.push_back(&sphere3);
	*/
	addCube();
	addSphere();
	addPlane();
	addCylinder();
	grid = Grid(plane);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);
	GLuint rotatebuffer;
	glGenBuffers(1, &rotatebuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rotatebuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_rotates.size() * sizeof(glm::mat4), &indexed_rotates[0], GL_STATIC_DRAW);
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	do{

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0/double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		grid.hashGrid(c3,cylinder,sphere);
		grid.checkCollisionGrid();
		computeMatricesFromInputs();
		grid.clearGrid();
		onPress();

		glm::mat4 ModelMatrix = mat4(1.0f);
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		for (int i = 0; i < c3.size(); i++)
		{
			(*c3[i]).updatePosition(timeStep);
			glm::mat4 ScaleMatrix = mat4();
			glm::mat4 RotateMatrix = (*c3[i]).getRotationMatrix();
			glm::mat4 TranslateMatrix = (*c3[i]).getTranslationMatrix();
			glPushMatrix();
			glUniformMatrix4fv(ScaleMatrixID, 1, GL_FALSE, &ScaleMatrix[0][0]);
			glUniformMatrix4fv(RotateMatrixID, 1, GL_FALSE, &RotateMatrix[0][0]);
			glUniformMatrix4fv(TranslateMatrixID, 1, GL_FALSE, &TranslateMatrix[0][0]);
			(*c3[i]).render();
			glPopMatrix();
		}
		for (int i = 0; i < sphere.size(); i++)
		{
			(*sphere[i]).updatePosition(timeStep);
			glm::mat4 ScaleMatrix = mat4();
			glm::mat4 RotateMatrix = (*sphere[i]).getRotationMatrix();
			glm::mat4 TranslateMatrix = (*sphere[i]).getTranslationMatrix();
			glPushMatrix();
			glUniformMatrix4fv(ScaleMatrixID, 1, GL_FALSE, &ScaleMatrix[0][0]);
			glUniformMatrix4fv(RotateMatrixID, 1, GL_FALSE, &RotateMatrix[0][0]);
			glUniformMatrix4fv(TranslateMatrixID, 1, GL_FALSE, &TranslateMatrix[0][0]);
			(*sphere[i]).render();
			glPopMatrix();
		}
		for (int i = 0; i < cylinder.size(); i++)
		{
			(*cylinder[i]).updatePosition(0.01f);
			glm::mat4 ScaleMatrix = mat4();
			glm::mat4 RotateMatrix = (*cylinder[i]).getRotationMatrix();
			glm::mat4 TranslateMatrix = (*cylinder[i]).getTranslationMatrix();
			glPushMatrix();
			glUniformMatrix4fv(ScaleMatrixID, 1, GL_FALSE, &ScaleMatrix[0][0]);
			glUniformMatrix4fv(RotateMatrixID, 1, GL_FALSE, &RotateMatrix[0][0]);
			glUniformMatrix4fv(TranslateMatrixID, 1, GL_FALSE, &TranslateMatrix[0][0]);
			(*cylinder[i]).render();
			glPopMatrix();
		}
		for (int i = 0; i < plane.size(); i++)
		{
			(*plane[i]).updatePosition(0.01f);
			glm::mat4 ScaleMatrix = mat4();
			glm::mat4 RotateMatrix = (*plane[i]).getRotationMatrix();
			glm::mat4 TranslateMatrix = (*plane[i]).getTranslationMatrix();
			glPushMatrix();
			glUniformMatrix4fv(ScaleMatrixID, 1, GL_FALSE, &ScaleMatrix[0][0]);
			glUniformMatrix4fv(RotateMatrixID, 1, GL_FALSE, &RotateMatrix[0][0]);
			glUniformMatrix4fv(TranslateMatrixID, 1, GL_FALSE, &TranslateMatrix[0][0]);
			(*plane[i]).render();
			glPopMatrix();
		}
		glm::mat4 ScaleMatrix = mat4();
		glm::mat4 RotateMatrix = mat4();
		glm::mat4 TranslateMatrix = mat4();
		glUniformMatrix4fv(ScaleMatrixID, 1, GL_FALSE, &ScaleMatrix[0][0]);
		glUniformMatrix4fv(RotateMatrixID, 1, GL_FALSE, &RotateMatrix[0][0]);
		glUniformMatrix4fv(TranslateMatrixID, 1, GL_FALSE, &TranslateMatrix[0][0]);
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(4,4,4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		//1rst attribute buffer : vertices
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			vertexPosition_modelspaceID,  // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
			);
		glEnableVertexAttribArray(vertexRotation_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, rotatebuffer);
		glVertexAttribPointer(
			vertexRotation_modelspaceID,  // The attribute we want to configure
			16,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
			);
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(vertexUVID);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			vertexUVID,                   // The attribute we want to configure
			2,                            // size : U+V => 2
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
			);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(vertexNormal_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			vertexNormal_modelspaceID,    // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
			);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_SHORT, // type
			(void*)0           // element array buffer offset
			);

		glDisableVertexAttribArray(vertexPosition_modelspaceID);
		glDisableVertexAttribArray(vertexRotation_modelspaceID);
		glDisableVertexAttribArray(vertexUVID);
		glDisableVertexAttribArray(vertexNormal_modelspaceID);

		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glColor3f(0.0f,0.5f,0.0f);
		gluCylinder(gluNewQuadric(),0.1,0.1,1,20,2);
		GLUquadric* sphere;
		sphere=gluNewQuadric();
		gluQuadricNormals(sphere, GL_SMOOTH);
		glColor3f(1,0,0);
		gluSphere(sphere,0.2,10,10);
		// Swap buffers
		glfwSwapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		glfwGetWindowParam( GLFW_OPENED ) );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &rotatebuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
