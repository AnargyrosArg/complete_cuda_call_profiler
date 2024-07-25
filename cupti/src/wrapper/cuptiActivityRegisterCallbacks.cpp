#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityRegisterCallbacks(CUpti_BuffersCallbackRequestFunc funcBufferRequested, CUpti_BuffersCallbackCompleteFunc funcBufferCompleted)
{
	CUptiResult retval = cuptiActivityRegisterCallbacks(funcBufferRequested, funcBufferCompleted);
	return retval;
}