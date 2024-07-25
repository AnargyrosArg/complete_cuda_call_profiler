#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetResultString(CUptiResult result, const char **str)
{
	CUptiResult retval = cuptiGetResultString(result, str);
	return retval;
}