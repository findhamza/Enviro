#pragma once
#ifndef LEARNERS_H
#define LEARNERS_H

#include <stdio.h>
#include <SDL.h>
#undef main
#include "objloader.h"
#include <SDL_opengl.h>
#include <gl/GL.h>
#include <iostream>

//FPS TIMER
const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

//WINDOW SIZE
const int _WIDTH = 1024;
const int _HEIGHT = 576;
const int _RATIO = _WIDTH / _HEIGHT;

//ARGS
bool _RUNNING = true;

//FUNCS
bool ProcessInput();

#endif