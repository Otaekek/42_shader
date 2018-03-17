#ifndef JOJISHI_HPP
#define JOJISHI_HPP

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#define assertf(x, f) if (x == 0) {printf("Assert failed in %s Line %d: %s\n", __FILE__, __LINE__, f); } 

#endif