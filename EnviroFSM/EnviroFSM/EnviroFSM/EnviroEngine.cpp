#include "EnviroEngine.h"

EnviroEngine* EnviroEngine::instance = 0;

bool EnviroEngine::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	// glfw: initialize and configure
	// ------------------------------
	//Icons made by Freepik from www.flaticon.com
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);


	// glfw window creation
	// --------------------
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	// build and compile our shader program
// ------------------------------------
	//Shader Loader
	mainShader = Shader("shader.vert", "shader.frag");

	//Antialiasing
	glEnable(GL_MULTISAMPLE);

	setupObjects();

	return true;
}

void EnviroEngine::setupObjects()
{
	do {
		plantA.plantInput(randomBool(), randomBool(), 5);
	} while (plantA.getTestState());

	sun.generateRim(); sun.generateSunVertices(); sun.generateSunIndices();
	std::vector<Vertex> sunVert = sun.getSunVertex();
	std::vector<unsigned int> sunInds = sun.getSunUIndices();
	sunObject = Mesh(sunVert, sunInds);

	plantA.drawTree();
	std::vector<Vertex> plantVert = plantA.getPlantVertex();
	std::vector<unsigned int> plantInds = plantA.getPlantUIndices();
	plantObject = Mesh(plantVert, plantInds);
}

bool EnviroEngine::running()
{
	return !glfwWindowShouldClose(window);
}

void EnviroEngine::handleEvents()
{
	processInput(window);
}

void EnviroEngine::update()
{
	//this is where we would update world enviornments
	//this area was previously used ot setup draw calls to opengl, now its handled by Mesh.h
	sun.updateSun();
	std::vector<Vertex> sunVert = sun.getSunVertex();
	std::vector<unsigned int> sunInds = sun.getSunUIndices();
	sunObject = Mesh(sunVert, sunInds);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void EnviroEngine::render()
{
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //werid teal color
	glClearColor(0.490f, 0.752f, 0.968f, 1.0f); //malibu blue
	glClear(GL_COLOR_BUFFER_BIT);
	// draw our first triangle
	//glUseProgram(shaderProgram);
	//mainShader.use();
	sunObject.Draw(mainShader);
	plantObject.Draw(mainShader);

}

void EnviroEngine::clean()
{
	quit();
}

void EnviroEngine::quit()
{
	glfwTerminate();
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

std::string getShader(std::string fileName)
{
	std::ifstream infileVert(fileName, std::fstream::in);
	std::string ShaderContent;
	if (infileVert.is_open())
		ShaderContent = std::string(std::istreambuf_iterator<char>(infileVert),
			std::istreambuf_iterator<char>());

	return ShaderContent;
}

float randomFloat() {
	std::default_random_engine rndEngine;
	rndEngine.seed(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	static auto gen = std::bind(std::uniform_real_distribution<>(0, 1), rndEngine);
	return gen();
}

bool randomBool() {
	std::default_random_engine rndEngine;
	rndEngine.seed(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), rndEngine);
	return gen();
}