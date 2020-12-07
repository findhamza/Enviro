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
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	window = glfwCreateWindow(fullscreen ? mode->width : width, 
								fullscreen ? mode->height : height,
								title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
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
	sunShader = Shader("sun.vert", "sun.frag");
	cloudShader = Shader("cloud.vert", "cloud.frag");
	rainShader = Shader("rain.vert", "rain.frag");

	//Antialiasing
	glEnable(GL_MULTISAMPLE);

	setupObjects();

	return true;
}

void EnviroEngine::setupObjects()
{
	std::thread sunThread_0(&TheSun::generateRim, &sun);
	std::thread cloudThread_0(&TheCloud::generateCloud, &clouds);
	std::thread plantThread_0(&PlantObject::drawTree, &plantA);

	sunThread_0.join();
	cloudThread_0.join();
	plantThread_0.join();

	/*sun.generateRim();*/ sun.generateSunVertices(); sun.generateSunIndices();
	std::vector<Vertex> sunVert = sun.getSunVertex();
	std::vector<unsigned int> sunInds = sun.getSunUIndices();
	sunObject = Mesh(sunVert, sunInds, 1);

	//clouds.generateCloud();
	std::vector<Vertex> cloudVert = clouds.getCloudVertex();
	std::vector<unsigned int> cloudInds = clouds.getCloudIndices();
	cloudObject = Mesh(cloudVert, cloudInds, 2);

	//plantA.drawTree();
	std::vector<Vertex> plantVert = plantA.getPlantVertex();
	std::vector<unsigned int> plantInds = plantA.getPlantUIndices();
	plantObject = Mesh(plantVert, plantInds, 3);

	rain = Mesh::ParticleGenerator(rainShader, 9999);
}

bool EnviroEngine::running()
{
	return !glfwWindowShouldClose(window);
}

void EnviroEngine::handleEvents()
{
	processInput(window);
}

void EnviroEngine::update(float dt, updateFlag uFlag)
{
	//this is where we would update world enviornments
	//this area was previously used ot setup draw calls to opengl, now its handled by Mesh.h
	//sun.updateSun();
	std::thread sunThread_0(&TheSun::updateSun, &sun);
	std::vector<Vertex> sunVert = sun.getSunVertex();
	std::vector<unsigned int> sunInds = sun.getSunUIndices();
	
	sunObject.Update(sunVert, sunInds);

	//plantObject.UpdateInds(plantA.updateTreeInds());
	std::thread plantThread_0(&Mesh::UpdateInds, &plantObject, plantA.updateTreeInds(uFlag));

	//std::vector<unsigned int> cloudInds = clouds.updateCloud();
	//cloudObject.UpdateInds(cloudInds);
	
	sunThread_0.join();
	plantThread_0.join();

	
	if (uFlag.cloud.rain == true) {
		if (rainDensity < .5)
			rainDensity = .5;
		rainDensity *= rainFactor;
	}
	else
		rainDensity /= rainFactor;
	rain.Update(0.5f, rainDensity, glm::vec2(0.0f, 0.0f));

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void EnviroEngine::render(updateFlag uFlags)
{
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //werid teal color
	glm::vec4 sky = sun.getSkyColor();
	glClearColor(sky.x,sky.y,sky.z,sky.a); //malibu blue
	glClear(GL_COLOR_BUFFER_BIT);
	// draw our first triangle
	//glUseProgram(shaderProgram);
	//mainShader.use();
	sunObject.Draw(sunShader);
	rain.Draw();
	cloudObject.Draw(cloudShader);
	plantObject.Draw(mainShader);
}

void EnviroEngine::clean()
{
	quit();
}

double EnviroEngine::getSunPowerLevel()
{
	return sun.getSunPower();
}

void EnviroEngine::quit()
{
	glfwTerminate();
}

void EnviroEngine::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		_fullscreen ^= true;
		if (_fullscreen)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowMonitor(window, _fullscreen ? glfwGetPrimaryMonitor() : NULL, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
		}
		else
			glfwSetWindowMonitor(window, NULL, 100, 100, 640, 480, GLFW_DONT_CARE);
	}
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