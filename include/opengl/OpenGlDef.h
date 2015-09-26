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

#elif defined(__APPLE__)

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

//iOS and Simulator
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>

#else

//OSX
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>

#endif

#elif defined(__linux__) || defined(__FreeBSD__)

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#endif

#ifdef _DEBUG
#define CHECKGLERROR() { auto errorCode = glGetError(); assert(errorCode == GL_NO_ERROR); }
#else
#define CHECKGLERROR()
#endif
