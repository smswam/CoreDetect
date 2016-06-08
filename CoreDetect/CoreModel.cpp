#include "stdafx.h"
#include "CoreModel.h"


BOOL CoreModel::isIntel()
{
	return Intel;
}


BOOL CoreModel::isAMD()
{
	return AMD;
}


CoreModel::CoreModel()
{
    Intel = false;
    AMD = false;
}


CoreModel::~CoreModel()
{
    
}
