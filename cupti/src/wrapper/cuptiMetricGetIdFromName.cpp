#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiMetricGetIdFromName(CUdevice device, const char *metricName, CUpti_MetricID *metric)
{
	CUptiResult retval = cuptiMetricGetIdFromName(device, metricName, metric);
	return retval;
}