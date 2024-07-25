#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiMetricGetNumEvents(CUpti_MetricID metric, uint32_t *numEvents)
{
	CUptiResult retval = cuptiMetricGetNumEvents(metric, numEvents);
	return retval;
}