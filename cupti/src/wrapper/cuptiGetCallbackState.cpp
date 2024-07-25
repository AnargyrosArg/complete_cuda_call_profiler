#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiGetCallbackState(uint32_t *enable, CUpti_SubscriberHandle subscriber, CUpti_CallbackDomain domain, CUpti_CallbackId cbid)
{
	CUptiResult retval = cuptiGetCallbackState(enable, subscriber, domain, cbid);
	return retval;
}