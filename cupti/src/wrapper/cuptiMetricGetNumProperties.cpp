#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiMetricGetNumProperties(CUpti_MetricID metric, uint32_t *numProp)
{
	CUptiResult retval = cuptiMetricGetNumProperties(metric, numProp);
	return retval;
}