#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiSetThreadIdType(CUpti_ActivityThreadIdType type)
{
	CUptiResult retval = cuptiSetThreadIdType(type);
	return retval;
}