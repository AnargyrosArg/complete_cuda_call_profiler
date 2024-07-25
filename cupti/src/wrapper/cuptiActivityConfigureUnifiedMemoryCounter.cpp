#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityConfigureUnifiedMemoryCounter(CUpti_ActivityUnifiedMemoryCounterConfig *config, uint32_t count)
{
	CUptiResult retval = cuptiActivityConfigureUnifiedMemoryCounter(config, count);
	return retval;
}