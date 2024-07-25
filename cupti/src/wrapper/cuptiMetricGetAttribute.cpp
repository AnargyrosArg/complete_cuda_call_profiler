#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiMetricGetAttribute(CUpti_MetricID metric, CUpti_MetricAttribute attrib, size_t *valueSize, void *value)
{
	CUptiResult retval = cuptiMetricGetAttribute(metric, attrib, valueSize, value);
	return retval;
}