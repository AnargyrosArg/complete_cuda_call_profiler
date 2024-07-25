#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiMetricGetValue(CUdevice device, CUpti_MetricID metric, size_t eventIdArraySizeBytes, CUpti_EventID *eventIdArray, size_t eventValueArraySizeBytes, uint64_t *eventValueArray, uint64_t timeDuration, CUpti_MetricValue *metricValue)
{
	CUptiResult retval = cuptiMetricGetValue(device, metric, eventIdArraySizeBytes, eventIdArray, eventValueArraySizeBytes, eventValueArray, timeDuration, metricValue);
	return retval;
}