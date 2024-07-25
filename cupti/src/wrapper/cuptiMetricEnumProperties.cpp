#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiMetricEnumProperties(CUpti_MetricID metric, size_t *propIdArraySizeBytes, CUpti_MetricPropertyID *propIdArray)
{
	CUptiResult retval = cuptiMetricEnumProperties(metric, propIdArraySizeBytes, propIdArray);
	return retval;
}