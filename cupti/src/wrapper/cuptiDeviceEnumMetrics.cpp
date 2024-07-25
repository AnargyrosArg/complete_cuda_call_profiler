#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiDeviceEnumMetrics(CUdevice device, size_t *arraySizeBytes, CUpti_MetricID *metricArray)
{
	CUptiResult retval = cuptiDeviceEnumMetrics(device, arraySizeBytes, metricArray);
	return retval;
}