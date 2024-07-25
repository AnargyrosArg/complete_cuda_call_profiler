#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetGraphNodeId(CUgraphNode node, uint64_t *nodeId)
{
	CUptiResult retval = cuptiGetGraphNodeId(node, nodeId);
	return retval;
}