#pragma once

#ifdef WIN32
#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#elif defined(__ANDROID__)
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>
#endif

#ifdef _DEBUG
#define CHECKGLERROR() { auto errorCode = glGetError(); assert(errorCode == GL_NO_ERROR); }
#else
#define CHECKGLERROR()
#endif
