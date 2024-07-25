#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtCreate)(cublasLtHandle_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtCreate(cublasLtHandle_t *lightHandle) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtCreate = (cublasStatus_t (*)(cublasLtHandle_t *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtCreate");
			fprintf(stderr, "wrapper_cublasLtCreate:%p\n", wrapper_cublasLtCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtCreate(lightHandle);
		return retval;
	}
}