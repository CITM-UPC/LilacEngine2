#pragma once

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <shellapi.h>
#include <set>
#include <memory>
#include <vector>
#include <array>
#include <filesystem>
#include <span>
#include <list>
#include <utility>
#include <algorithm>
#include <gl/glew.h>
#include <sstream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

typedef unsigned int uint;
using namespace std;
using namespace chrono;
namespace fs = std::filesystem;
using namespace std::chrono_literals;

static const unsigned int WINDOW_WIDTH = 576 * 4 / 3;
static const unsigned int WINDOW_HEIGHT = 576;
static const unsigned int FPS = 60;
static const auto FDT = 1.0s / FPS;

/// Releasing Memory
#define RELEASE( x )\
    {\
       if( x != nullptr )\
       {\
         delete x;\
	     x = nullptr;\
       }\
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x )\
	{\
	if( x != NULL )\
		{\
	  delete[] x;\
	  x = NULL;\
		}\
	}