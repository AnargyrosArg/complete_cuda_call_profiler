#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiMetricGetRequiredEventGroupSets(CUcontext context, CUpti_MetricID metric, CUpti_EventGroupSets **eventGroupSets)
{
	CUptiResult retval = cuptiMetricGetRequiredEventGroupSets(context, metric, eventGroupSets);
	return retval;
}