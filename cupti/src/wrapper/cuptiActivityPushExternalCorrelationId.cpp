#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityPushExternalCorrelationId(CUpti_ExternalCorrelationKind kind, uint64_t id)
{
	CUptiResult retval = cuptiActivityPushExternalCorrelationId(kind, id);
	return retval;
}