#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>

#pragma once
class CoreModel
{
public:
	BOOL Intel;
	BOOL AMD;

<<<<<<< HEAD
	BOOL isIntel();
	BOOL isAMD();
=======
	BOOL isIntel() { return Intel; }
	BOOL isAMD() { return AMD; }
>>>>>>> 0315703... Add files via upload

	CoreModel();
	~CoreModel();
};

