#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetGraphId(CUgraph graph, uint32_t *pId)
{
	CUptiResult retval = cuptiGetGraphId(graph, pId);
	return retval;
}