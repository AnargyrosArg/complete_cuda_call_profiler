#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityEnableAndDump(CUpti_ActivityKind kind)
{
	CUptiResult retval = cuptiActivityEnableAndDump(kind);
	return retval;
}