#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityPopExternalCorrelationId(CUpti_ExternalCorrelationKind kind, uint64_t *lastId)
{
	CUptiResult retval = cuptiActivityPopExternalCorrelationId(kind, lastId);
	return retval;
}