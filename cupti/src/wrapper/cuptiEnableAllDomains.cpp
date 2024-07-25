#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiEnableAllDomains(uint32_t enable, CUpti_SubscriberHandle subscriber)
{
	CUptiResult retval = cuptiEnableAllDomains(enable, subscriber);
	return retval;
}