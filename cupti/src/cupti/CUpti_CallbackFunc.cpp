/*#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_CUpti_CallbackFunc)(void *, CUpti_CallbackDomain, CUpti_CallbackId, const void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	void CUpti_CallbackFunc(void *userdata, CUpti_CallbackDomain domain, CUpti_CallbackId cbid, const void *cbdata) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_CUpti_CallbackFunc)
		{
			//fetch the original function addr using dlsym
			wrapper_CUpti_CallbackFunc = (void (*)(void *, CUpti_CallbackDomain, CUpti_CallbackId, const void *)) dlsym(libwrapper_cupti_handle, "wrapper_CUpti_CallbackFunc");
			fprintf(stderr, "wrapper_CUpti_CallbackFunc:%p\n", wrapper_CUpti_CallbackFunc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function CUpti_CallbackFunc():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_CUpti_CallbackFunc(userdata, domain, cbid, cbdata);
	}
}
*/
