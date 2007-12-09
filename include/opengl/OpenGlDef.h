#ifndef _OPENGLDEF_H_
#define _OPENGLDEF_H_

#ifdef WIN32
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>
#endif

#endif
