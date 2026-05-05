// Laura Reyes Carrillo
// Keyframes
// 3 de Mayo de 2026
// Practica 12 
// 320015764

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

//para json 
#include <fstream>
#include "json.hpp"
#include <string>
#include <sstream>

using json = nlohmann::json;


// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void Animation();
void saveAnimationJSON(const char* filename);
void loadAnimationJSON(const char* filename);
std::string getNextAnimationFilename();
void saveAnimationAutoJSON();
std::string getSelectedAnimationFilename();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;
int selectedAnimation = 1;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


glm::vec3 Light1 = glm::vec3(0);
//Anim
float rotBall = 0.0f;
float rotDog = 0.0f;
float rotDogX = 0.0f;
float rotDogZ = 0.0f;
int dogAnim = 0;
float FLegs = 0.0f;
float RLegs = 0.0f;
float head = 0.0f;
float tail = 0.0f;
float FLeftLeg = 0.0f;
float FRightLeg = 0.0f;
float BLeftLeg = 0.0f;
float BRightLeg = 0.0f;




//KeyFrames
float dogPosX , dogPosY , dogPosZ  ;

#define MAX_FRAMES 30
int i_max_steps = 190;
int i_curr_steps = 0;
typedef struct _frame {
	
	float rotDog;
	float rotDogInc;
	float rotDogX;
	float rotDogXInc;
	float rotDogZ;
	float rotDogZInc;
	float dogPosX;
	float dogPosY;
	float dogPosZ;
	float incX;
	float incY;
	float incZ;
	float head;
	float headInc;
	float tail;
	float tailInc;
	float FLeftLeg;
	float FLeftLegInc;
	float FRightLeg;
	float FRightLegInc;
	float BLeftLeg;
	float BLeftLegInc;
	float BRightLeg;
	float BRightLegInc;




}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].dogPosX = dogPosX;
	KeyFrame[FrameIndex].dogPosY = dogPosY;
	KeyFrame[FrameIndex].dogPosZ = dogPosZ;

	KeyFrame[FrameIndex].rotDog = rotDog;
	KeyFrame[FrameIndex].rotDogX = rotDogX;
	KeyFrame[FrameIndex].rotDogZ = rotDogZ;
	KeyFrame[FrameIndex].head = head;
	KeyFrame[FrameIndex].tail = tail;

	KeyFrame[FrameIndex].FLeftLeg = FLeftLeg;
	KeyFrame[FrameIndex].FRightLeg = FRightLeg;
	KeyFrame[FrameIndex].BLeftLeg = BLeftLeg;
	KeyFrame[FrameIndex].BRightLeg = BRightLeg;

	FrameIndex++;
}

void resetElements(void)
{
	dogPosX = KeyFrame[0].dogPosX;
	dogPosY = KeyFrame[0].dogPosY;
	dogPosZ = KeyFrame[0].dogPosZ;
	head = KeyFrame[0].head;
	tail = KeyFrame[0].tail;

	FLeftLeg = KeyFrame[0].FLeftLeg;
	FRightLeg = KeyFrame[0].FRightLeg;
	BLeftLeg = KeyFrame[0].BLeftLeg;
	BRightLeg = KeyFrame[0].BRightLeg;


	rotDog = KeyFrame[0].rotDog;
	rotDogX = KeyFrame[0].rotDogX;
	rotDogZ = KeyFrame[0].rotDogZ;

}


void saveAnimationJSON(const char* filename)
{
	json animation;

	animation["totalFrames"] = FrameIndex;
	animation["maxSteps"] = i_max_steps;
	animation["keyframes"] = json::array();

	for (int i = 0; i < FrameIndex; i++)
	{
		json frame;

		frame["dogPosX"] = KeyFrame[i].dogPosX;
		frame["dogPosY"] = KeyFrame[i].dogPosY;
		frame["dogPosZ"] = KeyFrame[i].dogPosZ;

		frame["rotDog"] = KeyFrame[i].rotDog;
		frame["rotDogX"] = KeyFrame[i].rotDogX;
		frame["rotDogZ"] = KeyFrame[i].rotDogZ;

		frame["head"] = KeyFrame[i].head;
		frame["tail"] = KeyFrame[i].tail;

		frame["FLeftLeg"] = KeyFrame[i].FLeftLeg;
		frame["FRightLeg"] = KeyFrame[i].FRightLeg;

		frame["BLeftLeg"] = KeyFrame[i].BLeftLeg;
		frame["BRightLeg"] = KeyFrame[i].BRightLeg;

		animation["keyframes"].push_back(frame);
	}

	std::ofstream file(filename);

	if (!file.is_open())
	{
		printf("No se pudo crear el archivo JSON\n");
		return;
	}

	file << animation.dump(4);
	file.close();

	printf("Animacion guardada en %s\n", filename);
}

void loadAnimationJSON(const char* filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		printf("No se pudo abrir el archivo JSON\n");
		return;
	}

	json animation;
	file >> animation;
	file.close();

	FrameIndex = animation["totalFrames"];
	i_max_steps = animation["maxSteps"];

	if (FrameIndex > MAX_FRAMES)
	{
		printf("El archivo tiene mas frames que MAX_FRAMES. Se cargaran solo %d frames\n", MAX_FRAMES);
		FrameIndex = MAX_FRAMES;
	}

	for (int i = 0; i < FrameIndex; i++)
	{
		KeyFrame[i].dogPosX = animation["keyframes"][i]["dogPosX"];
		KeyFrame[i].dogPosY = animation["keyframes"][i]["dogPosY"];
		KeyFrame[i].dogPosZ = animation["keyframes"][i]["dogPosZ"];

		KeyFrame[i].rotDog = animation["keyframes"][i]["rotDog"];
		KeyFrame[i].rotDogX = animation["keyframes"][i]["rotDogX"];
		KeyFrame[i].rotDogZ = animation["keyframes"][i]["rotDogZ"];

		KeyFrame[i].head = animation["keyframes"][i]["head"];
		KeyFrame[i].tail = animation["keyframes"][i]["tail"];

		KeyFrame[i].FLeftLeg = animation["keyframes"][i]["FLeftLeg"];
		KeyFrame[i].FRightLeg = animation["keyframes"][i]["FRightLeg"];

		KeyFrame[i].BLeftLeg = animation["keyframes"][i]["BLeftLeg"];
		KeyFrame[i].BRightLeg = animation["keyframes"][i]["BRightLeg"];
	}

	resetElements();

	printf("Animacion cargada desde %s\n", filename);
}

std::string getNextAnimationFilename()
{
	int number = 1;

	while (true)
	{
		std::stringstream ss;
		ss << "animacion_" << number << ".json";

		std::ifstream file(ss.str());

		// Si el archivo no existe, ese nombre está libre
		if (!file.good())
		{
			return ss.str();
		}

		file.close();
		number++;
	}
}

void saveAnimationAutoJSON()
{
	if (FrameIndex <= 0)
	{
		printf("No hay keyframes para guardar.\n");
		return;
	}

	std::string filename = getNextAnimationFilename();

	saveAnimationJSON(filename.c_str());

	printf("Animacion guardada automaticamente como: %s\n", filename.c_str());
}

std::string getSelectedAnimationFilename()
{
	std::stringstream ss;
	ss << "animacion_" << selectedAnimation << ".json";
	return ss.str();
}




void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].dogPosX - KeyFrame[playIndex].dogPosX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].dogPosY - KeyFrame[playIndex].dogPosY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].dogPosZ - KeyFrame[playIndex].dogPosZ) / i_max_steps;
	KeyFrame[playIndex].headInc = (KeyFrame[playIndex + 1].head - KeyFrame[playIndex].head) / i_max_steps;

	KeyFrame[playIndex].rotDogInc = (KeyFrame[playIndex + 1].rotDog - KeyFrame[playIndex].rotDog) / i_max_steps;
	KeyFrame[playIndex].rotDogXInc = (KeyFrame[playIndex + 1].rotDogX - KeyFrame[playIndex].rotDogX) / i_max_steps;
	KeyFrame[playIndex].rotDogZInc = (KeyFrame[playIndex + 1].rotDogZ - KeyFrame[playIndex].rotDogZ) / i_max_steps;

	KeyFrame[playIndex].tailInc = (KeyFrame[playIndex + 1].tail - KeyFrame[playIndex].tail) / i_max_steps;
	KeyFrame[playIndex].FLeftLegInc = (KeyFrame[playIndex + 1].FLeftLeg - KeyFrame[playIndex].FLeftLeg) / i_max_steps;
	KeyFrame[playIndex].FRightLegInc = (KeyFrame[playIndex + 1].FRightLeg - KeyFrame[playIndex].FRightLeg) / i_max_steps;
	KeyFrame[playIndex].BLeftLegInc = (KeyFrame[playIndex + 1].BLeftLeg - KeyFrame[playIndex].BLeftLeg) / i_max_steps;
	KeyFrame[playIndex].BRightLegInc = (KeyFrame[playIndex + 1].BRightLeg - KeyFrame[playIndex].BRightLeg) / i_max_steps;

}



// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Laura Reyes Carrillo - Keyframes", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	
	
	//models
	Model DogBody((char*)"Models/DogBody.obj");
	Model HeadDog((char*)"Models/HeadDog.obj");
	Model DogTail((char*)"Models/TailDog.obj");
	Model F_RightLeg((char*)"Models/F_RightLegDog.obj");
	Model F_LeftLeg((char*)"Models/F_LeftLegDog.obj");
	Model B_RightLeg((char*)"Models/B_RightLegDog.obj");
	Model B_LeftLeg((char*)"Models/B_LeftLegDog.obj");
	Model Piso((char*)"Models/piso.obj");
	Model Ball((char*)"Models/ball.obj");


	//KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].dogPosX = 0;
		KeyFrame[i].dogPosY = 0;
		KeyFrame[i].dogPosZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotDog = 0;
		KeyFrame[i].rotDogInc = 0;
		KeyFrame[i].rotDogX = 0;
		KeyFrame[i].rotDogXInc = 0;
		KeyFrame[i].rotDogZ = 0;
		KeyFrame[i].rotDogZInc = 0;
		KeyFrame[i].head = 0;
		KeyFrame[i].headInc = 0;
		KeyFrame[i].tail = 0;
		KeyFrame[i].tailInc = 0;
		KeyFrame[i].FLeftLeg = 0;
		KeyFrame[i].FLeftLegInc = 0;
		KeyFrame[i].FRightLeg = 0;
		KeyFrame[i].FRightLegInc = 0;
		KeyFrame[i].BLeftLeg = 0;
		KeyFrame[i].BLeftLegInc = 0;
		KeyFrame[i].BRightLeg = 0;
		KeyFrame[i].BRightLegInc = 0;


	}


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	
	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		
	

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"),0.6f,0.6f,0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"),0.3f, 0.3f, 0.3f);


		// Point light 1
	    glm::vec3 lightColor;
		lightColor.x= abs(sin(glfwGetTime() *Light1.x));
		lightColor.y= abs(sin(glfwGetTime() *Light1.y));
		lightColor.z= sin(glfwGetTime() *Light1.z);

		
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x,lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x,lightColor.y,lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"),0.075f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));
		

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);

	
		
		//Carga de modelo 
        view = camera.GetViewMatrix();	
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//Body
		modelTemp = model = glm::translate(model, glm::vec3(dogPosX, dogPosY, dogPosZ));
		// Rotación normal del perro, izquierda/derecha
		modelTemp = model = glm::rotate(model, glm::radians(rotDog), glm::vec3(0.0f, 1.0f, 0.0f));
		// Inclinación del perro para sentarse
		modelTemp = model = glm::rotate(model, glm::radians(rotDogX), glm::vec3(1.0f, 0.0f, 0.0f));
		// Rotación del perro alrededor del eje Z
		modelTemp = model = glm::rotate(model, glm::radians(rotDogZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DogBody.Draw(lightingShader);
		//Head
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));
		model = glm::rotate(model, glm::radians(head), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		HeadDog.Draw(lightingShader);
		//Tail 
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));
		model = glm::rotate(model, glm::radians(tail), glm::vec3(0.0f, 0.0f, -1.0f)); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		DogTail.Draw(lightingShader);
		//Front Left Leg
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));
		model = glm::rotate(model, glm::radians(FLeftLeg), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_LeftLeg.Draw(lightingShader);
		//Front Right Leg
		model = modelTemp; 
		model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));
		model = glm::rotate(model, glm::radians(FRightLeg), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_RightLeg.Draw(lightingShader);
		//Back Left Leg
		model = modelTemp; 
		model = glm::translate(model, glm::vec3(0.082f, -0.046, -0.218)); 
		model = glm::rotate(model, glm::radians(BLeftLeg), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		B_LeftLeg.Draw(lightingShader);
		//Back Right Leg
		model = modelTemp; 
		model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
		model = glm::rotate(model, glm::radians(BRightLeg), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		B_RightLeg.Draw(lightingShader); 


		//model = glm::mat4(1);
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		//model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	 //   Ball.Draw(lightingShader); 
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		//glBindVertexArray(0);
	

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		
		model = glm::mat4(1);
		model = glm::translate(model, pointLightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glBindVertexArray(0);

		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	
	

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	//Dog Controls
	//head
	if (keys[GLFW_KEY_4])
	{

		head += 1.0f;

	}
	if (keys[GLFW_KEY_5])
	{

		head -= 1.0f;

	}
	// Cola
	if (keys[GLFW_KEY_6])
	{
		tail += 1.0f;
	}

	if (keys[GLFW_KEY_7])
	{
		tail -= 1.0f;
	}

	// Rotación del perro en eje Z
	if (keys[GLFW_KEY_8])
	{
		rotDogZ += 1.0f;
	}

	if (keys[GLFW_KEY_9])
	{
		rotDogZ -= 1.0f;
	}

	// Pata delantera izquierda
	if (keys[GLFW_KEY_Z])
	{
		FLeftLeg += 1.0f;
	}

	if (keys[GLFW_KEY_X])
	{
		FLeftLeg -= 1.0f;
	}
	// Pata delantera derecha
	if (keys[GLFW_KEY_C])
	{
		FRightLeg += 1.0f;
	}

	if (keys[GLFW_KEY_V])
	{
		FRightLeg -= 1.0f;
	}
	// Pata trasera izquierda
	if (keys[GLFW_KEY_B])
	{
		BLeftLeg += 1.0f;
	}

	if (keys[GLFW_KEY_N])
	{
		BLeftLeg -= 1.0f;
	}
	// Pata trasera derecha
	if (keys[GLFW_KEY_M])
	{
		BRightLeg += 1.0f;
	}

	if (keys[GLFW_KEY_COMMA])
	{
		BRightLeg -= 1.0f;
	}
	// Mover perro hacia arriba y hacia abajo
	if (keys[GLFW_KEY_R])
	{
		dogPosY += 0.01f;   // Sube el perro
	}

	if (keys[GLFW_KEY_F])
	{
		dogPosY -= 0.01f;   // Baja el perro
	}
	// Rotación del perro en eje X para sentarse/inclinarse
	if (keys[GLFW_KEY_T])
	{
		rotDogX += 1.0f;
	}

	if (keys[GLFW_KEY_U])
	{
		rotDogX -= 1.0f;
	}

	
	if (keys[GLFW_KEY_2])
	{
		
			rotDog += 1.0f;

	}

	if (keys[GLFW_KEY_3])
	{
		
			rotDog -= 1.0f;

	}
			
	if (keys[GLFW_KEY_H])
	{
		dogPosZ += 0.01;
	}

	if (keys[GLFW_KEY_Y])
	{
		dogPosZ -= 0.01;
	}

	if (keys[GLFW_KEY_G])
	{
		dogPosX -= 0.01;
	}

	if (keys[GLFW_KEY_J])
	{
		dogPosX += 0.01;
	}

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	/*if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}*/
	if (keys[GLFW_KEY_Q])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_O])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_P])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	/*if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}*/
	if (keys[GLFW_KEY_I])
	{
		pointLightPositions[0].z += 0.01f;
	}
	
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	// Guardar keyframe
	if (key == GLFW_KEY_K && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
		else
		{
			printf("Ya no hay espacio para mas keyframes\n");
		}
	}

	// Reproducir o detener animacion
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			resetElements();
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;

			printf("Reproduciendo animacion\n");
		}
		else
		{
			play = false;
			printf("Animacion detenida\n");
		}
	}

	// Guardar animacion en JSON
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		saveAnimationAutoJSON();
	}
	// Cargar animacion desde JSON
	if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
	{
		std::string filename = getSelectedAnimationFilename();
		loadAnimationJSON(filename.c_str());
	}

	if (key == GLFW_KEY_F5 && action == GLFW_PRESS)
	{
		if (selectedAnimation > 1)
		{
			selectedAnimation--;
		}

		printf("Animacion seleccionada: animacion_%d.json\n", selectedAnimation);
	}

	if (key == GLFW_KEY_F6 && action == GLFW_PRESS)
	{
		selectedAnimation++;

		printf("Animacion seleccionada: animacion_%d.json\n", selectedAnimation);
	}

	// Activar o apagar luz
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		active = !active;

		if (active)
		{
			Light1 = glm::vec3(0.2f, 0.8f, 1.0f);
		}
		else
		{
			Light1 = glm::vec3(0);
		}
	}
}



void Animation() {

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			dogPosX += KeyFrame[playIndex].incX;
			dogPosY += KeyFrame[playIndex].incY;
			dogPosZ += KeyFrame[playIndex].incZ;
			head += KeyFrame[playIndex].headInc;
			tail += KeyFrame[playIndex].tailInc;
			FLeftLeg += KeyFrame[playIndex].FLeftLegInc;
			FRightLeg += KeyFrame[playIndex].FRightLegInc;
			BLeftLeg += KeyFrame[playIndex].BLeftLegInc;
			BRightLeg += KeyFrame[playIndex].BRightLegInc;

			rotDog += KeyFrame[playIndex].rotDogInc;
			rotDogX += KeyFrame[playIndex].rotDogXInc;
			rotDogZ += KeyFrame[playIndex].rotDogZInc;

			i_curr_steps++;
		}

	}
	
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}


