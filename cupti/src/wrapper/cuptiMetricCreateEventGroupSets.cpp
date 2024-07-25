#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiMetricCreateEventGroupSets(CUcontext context, size_t metricIdArraySizeBytes, CUpti_MetricID *metricIdArray, CUpti_EventGroupSets **eventGroupPasses)
{
	CUptiResult retval = cuptiMetricCreateEventGroupSets(context, metricIdArraySizeBytes, metricIdArray, eventGroupPasses);
	return retval;
}