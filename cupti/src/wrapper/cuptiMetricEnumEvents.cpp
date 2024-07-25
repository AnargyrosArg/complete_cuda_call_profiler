#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiMetricEnumEvents(CUpti_MetricID metric, size_t *eventIdArraySizeBytes, CUpti_EventID *eventIdArray)
{
	CUptiResult retval = cuptiMetricEnumEvents(metric, eventIdArraySizeBytes, eventIdArray);
	return retval;
}