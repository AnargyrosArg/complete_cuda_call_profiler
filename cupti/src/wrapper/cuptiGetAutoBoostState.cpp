#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetAutoBoostState(CUcontext context, CUpti_ActivityAutoBoostState *state)
{
	CUptiResult retval = cuptiGetAutoBoostState(context, state);
	return retval;
}