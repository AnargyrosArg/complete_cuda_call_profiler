#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
CUptiResult wrapper_cuptiSupportedDomains(size_t *domainCount, CUpti_DomainTable *domainTable)
{
	CUptiResult retval = cuptiSupportedDomains(domainCount, domainTable);
	return retval;
}