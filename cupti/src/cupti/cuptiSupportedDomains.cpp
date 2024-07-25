#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiSupportedDomains)(size_t *, CUpti_DomainTable *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiSupportedDomains(size_t *domainCount, CUpti_DomainTable *domainTable) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiSupportedDomains)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiSupportedDomains = (CUptiResult (*)(size_t *, CUpti_DomainTable *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiSupportedDomains");
			fprintf(stderr, "wrapper_cuptiSupportedDomains:%p\n", wrapper_cuptiSupportedDomains);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiSupportedDomains():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiSupportedDomains(domainCount, domainTable);
		return retval;
	}
}