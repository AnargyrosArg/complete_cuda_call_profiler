#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiActivityConfigurePCSampling(CUcontext ctx, CUpti_ActivityPCSamplingConfig *config)
{
	CUptiResult retval = cuptiActivityConfigurePCSampling(ctx, config);
	return retval;
}