#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


//Transform transform;
Transform mesh1_transform;
Transform mesh2_transform;
Transform mesh3_transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
	//Audio* audioDevice();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); // Initialises the system
	gameLoop(); // Loops the game
}

void MainGame::initSystems()
{
	_gameDisplay.DisplayInit();
	whistle = audioDevice.loadSound("..\\res\\bang.wav"); // load the bang.wav
	backGroundMusic = audioDevice.loadSound("..\\res\\backgroundmusic.wav");// loads the backgroundmusic.wav

	mesh1.loadModel("..\\res\\wolf.obj");// loads the wolf model
	mesh2.loadModel("..\\res\\cat.obj");// loads the cat model
	mesh3.loadModel("..\\res\\Moon.obj");// loads the moon model

	myCamera.initializeCamera(glm::vec3(80, -40, -250), 200.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);


	shader.init("..\\res\\shader"); //new shader

	counter = 2.0f;
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();

		collision(mesh1.GetSpherePos(), mesh1.GetSphereRadius() + 40, mesh2.GetSpherePos() + glm::vec3(-40,0,0), mesh2.GetSphereRadius()) + 40;
		//checks for collision between the meshes
		collision(mesh2.GetSpherePos(), mesh2.GetSphereRadius() + 40, mesh3.GetSpherePos(), mesh3.GetSphereRadius());
		collision(mesh1.GetSpherePos(), mesh1.GetSphereRadius() + 40, mesh3.GetSpherePos(), mesh3.GetSphereRadius());
		playAudio(backGroundMusic, glm::vec3(0.0f, 0.0f, 0.0f));

	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym)
			{
			case SDLK_ESCAPE:

				break;
			case SDLK_DOWN:
			{

			}
			break;

			case SDLK_d:
			{

				mesh1_transform.SetPos(glm::vec3(mesh1_transform.GetPosx() + counter, mesh1_transform.GetPosy(), mesh1_transform.GetPosz()));
				//changes the position of the wolf if D was pressed
				break;
			}
			case SDLK_a:
			{
				mesh1_transform.SetPos(glm::vec3(mesh1_transform.GetPosx()-counter, mesh1_transform.GetPosy(), mesh1_transform.GetPosz()));
				//changes the position of the wolf if A was pressed
				break;
			}
			case SDLK_w:
			{
				mesh1_transform.SetPos(glm::vec3(mesh1_transform.GetPosx(), mesh1_transform.GetPosy()-counter, mesh1_transform.GetPosz()));
				//changes the position of the wolf if W was pressed
				break;
			}
			case SDLK_s:
			{
				mesh1_transform.SetPos(glm::vec3(mesh1_transform.GetPosx(), mesh1_transform.GetPosy() + counter, mesh1_transform.GetPosz()));
				//changes the position of the wolf if S was pressed
				break;
			}

			}
		}
	}
}

bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = ((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

	if (distance * distance < (m1Rad + m2Rad))
	{
		audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
{

	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		audioDevice.playSound(Source, pos);// plays the sound 
	}
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f); // Clears the Display

	//transform.SetPos(glm::vec3(sinf(counter) / 5, 0.5, 0.0));
	//transform.SetPos(glm::vec3(0.5, 0.5, 0.0));
	//mesh1.m_transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));


	Texture texture("..\\res\\bricks.jpg"); //load texture
	Texture texture2("..\\res\\Cat_diffuse.jpg");//load texture
	Texture texture3("..\\res\\Moona.jpg"); //load texture

	//Mesh1 Drawing
	shader.Bind();//Binds the shader
	shader.Update(mesh1_transform, myCamera); //Updates the camera
	texture.Bind(0); // Bind the texture
	mesh1.draw(); //Draws the mesh
	mesh1_transform.SetRot(glm::vec3(3.50, 1.5, 0.0)); //Sets the rotation of the transform of the mesh
	mesh1_transform.SetScale(glm::vec3(80.0, 80.0, 80.0));//Sets the scale of the mesh
	mesh1.UpdateSphereData(*mesh1_transform.GetPos(), 0.62f);//Updates the sphere data of the mesh collision sphere
	
	//Mesh2 Drawing
	shader.Bind();//Binds the shader
	shader.Update(mesh2_transform, myCamera);//Updates the camera
	texture2.Bind(0);// Bind the texture
	mesh2.draw();	//Draws the mesh
	mesh2_transform.SetPos(glm::vec3(200.0, 0 , 0)); //Sets the position of the transform of the mesh
	mesh2_transform.SetRot(glm::vec3(2.0, 0.0, 1.5));//Sets the rotation of the mesh
	mesh2_transform.SetScale(glm::vec3(1.0, 1.0, 1.0));//Sets the scale of the mesh
	mesh2.UpdateSphereData(*mesh2_transform.GetPos(), 0.62f);//Updates the sphere data of the mesh collision sphere

	//Mesh3 Drawing
	shader.Bind();//Binds the shader
	shader.Update(mesh3_transform, myCamera);//Updates the camera
	texture3.Bind(0);// Bind the texture
	mesh3.draw();//Draws the mesh
	mesh3.UpdateSphereData(*mesh3_transform.GetPos(), 0.62f);//Updates the sphere data of the mesh collision sphere

	mesh3_transform.SetPos(glm::vec3(240, -160, 0));//Sets the position of the transform of the mesh
	mesh3_transform.SetRot(glm::vec3(0.0, 0.0, 0.0));//Sets the rotation of the mesh
	mesh3_transform.SetScale(glm::vec3(0.3, 0.3, 0.3));//Sets the scale of the mesh

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd(); // Ends GL

	_gameDisplay.swapBuffer(); // swaps the buffers
}