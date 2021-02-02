#include "Display.h"

Display::Display()
{
	sdlWindow = nullptr; //initialise to generate null access violation for debugging. 
	screenWidth = 1024.0f; // sets the screen Width
	screenHeight = 768.0f; // sets the screen Height
}

Display::~Display()
{
	SDL_GL_DeleteContext(glContext); // delete context
	SDL_DestroyWindow(sdlWindow); // detete window (make sure to delete the context and the window in the opposite order of creation in initDisplay())
	SDL_Quit(); // Quits SDL
}

float Display::getWidth() { return screenWidth; } //getters
float Display::getHeight() { return screenHeight; }

//returns Errors
void Display::returnError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}
//swap between the visible buffer and the drawing one
void Display::swapBuffer()
{
	SDL_GL_SwapWindow(sdlWindow); //swap buffers
}

//Clears the Dsiplay to a simple color which is set with the parameters
void Display::clearDisplay(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

//Initialise the Display using SDL
void Display::DisplayInit()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	sdlWindow = SDL_CreateWindow("Coursework_GP2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL); // create window

	if (sdlWindow == nullptr)
	{
		returnError("window didn't create");
	}

	glContext = SDL_GL_CreateContext(sdlWindow);

	if (glContext == nullptr)
	{
		returnError("SDL_GL context didn't create");
	}

	GLenum error = glewInit(); 
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}