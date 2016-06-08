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

	BOOL isIntel();
	BOOL isAMD();

	CoreModel();
	~CoreModel();
};

