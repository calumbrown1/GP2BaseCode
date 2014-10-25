//
//  Game.cpp
//  GP2BaseCode
//
//  Created by Brian on 21/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

#include "Game/Game.h"

GameApplication::GameApplication()
{
    m_pWindow=NULL;
    m_GLContext=NULL;
    m_isRunning=false;
    m_GameTitle="Game";
    m_WindowWidth=1280;
    m_WindowHeight=800;
    m_WindowFullscreen=false;
    
}

GameApplication::~GameApplication()
{
    destroy();
}

void GameApplication::destroy()
{
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

//Parse command line options
bool GameApplication::init(int argc, char * arg[])
{
    //Parse command line stuff
    
    // init everyting - SDL, if it is nonzero we have a problem
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init " <<SDL_GetError()<< std::endl;
        
        return false;
    }
    
	int imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags) & (imageInitFlags)) != imageInitFlags) {
		std::cout << "ERROR SDL_Image Init " << IMG_GetError() << std::endl;
        return false;
	}
    
	if (TTF_Init() == -1) {
		std::cout << "TTF_Init: " << TTF_GetError();
        return false;
	}
    
    
    if (!initWindow(m_GameTitle.c_str(),m_WindowWidth, m_WindowHeight, m_WindowFullscreen))
    {
        std::cout<<"ERROR unable to create windows"<<std::endl;
        return false;
    }
    
    if (!initGraphics())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Graphics Error", "Can't initialise Graphics", m_pWindow);
        return false;
    }
    if (!initInput())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Input Error", "Can't initialise Input", m_pWindow);
        return false;
    }
    if (!initAudio())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Audio Error", "Can't initialise Input", m_pWindow);
        return false;
    }
    
    m_isRunning=true;
    
    return true;
}

bool GameApplication::initWindow(const std::string& title,int width, int height,bool fullscreen)
{
	//Create a window
	m_pWindow = SDL_CreateWindow(
                              title.c_str(),             // window title
                              SDL_WINDOWPOS_CENTERED,     // x position, centered
                              SDL_WINDOWPOS_CENTERED,     // y position, centered
                              width,                        // width, in pixels
                              height,                        // height, in pixels
                              SDL_WINDOW_OPENGL           // flags
                              );
    if (!m_pWindow)
    {
        std::cout<<"Error: Window not initialised"<<std::endl;
        return false;
    }
    
    if (fullscreen)
    {
        SDL_SetWindowFullscreen(m_pWindow,SDL_WINDOW_FULLSCREEN);
        SDL_ShowCursor(0);
    }
    
    return true;
}

bool GameApplication::initGraphics()
{
    //Ask for version 3.2 of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
	//Create OpenGL Context
	m_GLContext = SDL_GL_CreateContext(m_pWindow);
    
    glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
        return false;
	}
    
    //Smooth shading
    glShadeModel( GL_SMOOTH );
    
    //clear the background to black
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    //Clear the depth buffer
    glClearDepth( 1.0f );
    
    //Enable depth testing
    glEnable( GL_DEPTH_TEST );
    
    //The depth test to go
    glDepthFunc( GL_LEQUAL );
    
    //Turn on best perspective correction
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    
    setViewport(1024,768);
    
    return true;
}

bool GameApplication::initInput()
{
    return true;
}

bool GameApplication::initAudio()
{
    return true;
}

void GameApplication::update()
{
    //check for events
    //Value to hold the event generated by SDL
    SDL_Event event;
    //While we still have events in the queue
    while (SDL_PollEvent(&event)) {
        //Get event type
        switch(event.type)
        {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:{
                OnClose();
                break;
            }
            case SDL_WINDOWEVENT_MINIMIZED:
            {
                break;
            }
            case SDL_WINDOWEVENT_MAXIMIZED:
            {
                break;
            }
            case SDL_KEYDOWN:
            {
                break;
            }
            case SDL_KEYUP:
            {
                break;
            }
            case SDL_MOUSEMOTION:
            {
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                break;
            }
        }

    }
}

void GameApplication::render()
{
    //old imediate mode!
    //Set the clear colour(background)
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    //clear the colour and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    
    SDL_GL_SwapWindow(m_pWindow);
}

//Function to set/reset viewport
void GameApplication::setViewport( int width, int height )
{
    
    //make sure height is always above 1
    if ( height == 0 ) {
        height = 1;
    }
    
    
    //Setup viewport
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
}

void GameApplication::OnClose()
{
    m_isRunning=false;
}



