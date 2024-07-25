#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityRegisterTimestampCallback(CUpti_TimestampCallbackFunc funcTimestamp)
{
	CUptiResult retval = cuptiActivityRegisterTimestampCallback(funcTimestamp);
	return retval;
}