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
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/quaternion_utils.hpp>
std::vector<unsigned short> indices;
std::vector<glm::vec3> indexed_vertices;
std::vector<glm::mat4> indexed_rotates;
std::vector<glm::vec2> indexed_uvs;
std::vector<glm::vec3> indexed_normals;
vec3 gPosition1(-1.5f, 0.0f, 0.0f);
vec3 gOrientation1;
 
vec3 gPosition2( 1.5f, 0.0f, 0.0f);
quat gOrientation2;
 
bool gLookAtOther = true;
void addCube(Cube cube){

}
int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

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
	vector<Cube> c3;
	Cube cube1= Cube(vec3(1,1,1),vec3(0,0,1),vec3(1,0,0),1,1);
	Cube cube2= Cube(vec3(0,1,0),vec3(0,2.5f,1),vec3(0,1,0),0.5f,1);
	Cube cube3= Cube(vec3(1,0,0),vec3(1,0,1),vec3(0,0,1),0.2f,1);
	c3.push_back(cube1);
	c3.push_back(cube2);
	c3.push_back(cube3);
	
	//cout<<"type = "<<typeid(cube1).name();
	
	vector<Sphere> sph;
	Sphere sphere1= Sphere(vec3(1,1,1),vec3(0,0,1),vec3(0,0,0),1,1);
	Sphere sphere2= Sphere(vec3(0,1,0),vec3(0,2.5f,1),vec3(0,0,0),0.5f,1);
	Sphere sphere3= Sphere(vec3(1,0,0),vec3(1,0,1),vec3(0,0,0),0.2f,1);
	sph.push_back(sphere1);
	sph.push_back(sphere2);
	sph.push_back(sphere3);
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
		computeMatricesFromInputs();
		glm::mat4 ModelMatrix = mat4(1.0f);
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		for (int i = 0; i < c3.size(); i++)
		{
			c3[i].updatePosition(0.01f);
			glm::mat4 ScaleMatrix = mat4();
			glm::mat4 RotateMatrix = c3[i].getRotationMatrix();
			glm::mat4 TranslateMatrix = c3[i].getTranslationMatrix();
			glPushMatrix();
			glUniformMatrix4fv(ScaleMatrixID, 1, GL_FALSE, &ScaleMatrix[0][0]);
			glUniformMatrix4fv(RotateMatrixID, 1, GL_FALSE, &RotateMatrix[0][0]);
			glUniformMatrix4fv(TranslateMatrixID, 1, GL_FALSE, &TranslateMatrix[0][0]);
			c3[i].renderCube(vec3(0,0,0));
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

