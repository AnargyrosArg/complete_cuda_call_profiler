#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiFinalize()
{
	CUptiResult retval = cuptiFinalize();
	return retval;
}