#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiMetricGetValue2(CUpti_MetricID metric, size_t eventIdArraySizeBytes, CUpti_EventID *eventIdArray, size_t eventValueArraySizeBytes, uint64_t *eventValueArray, size_t propIdArraySizeBytes, CUpti_MetricPropertyID *propIdArray, size_t propValueArraySizeBytes, uint64_t *propValueArray, CUpti_MetricValue *metricValue)
{
	CUptiResult retval = cuptiMetricGetValue2(metric, eventIdArraySizeBytes, eventIdArray, eventValueArraySizeBytes, eventValueArray, propIdArraySizeBytes, propIdArray, propValueArraySizeBytes, propValueArray, metricValue);
	return retval;
}