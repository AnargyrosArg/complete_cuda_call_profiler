#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiUnsubscribe(CUpti_SubscriberHandle subscriber)
{
	CUptiResult retval = cuptiUnsubscribe(subscriber);
	return retval;
}