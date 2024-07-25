#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetThreadIdType(CUpti_ActivityThreadIdType *type)
{
	CUptiResult retval = cuptiGetThreadIdType(type);
	return retval;
}