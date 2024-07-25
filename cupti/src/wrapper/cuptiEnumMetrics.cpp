#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEnumMetrics(size_t *arraySizeBytes, CUpti_MetricID *metricArray)
{
	CUptiResult retval = cuptiEnumMetrics(arraySizeBytes, metricArray);
	return retval;
}