#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCreate)(cusolverDnHandle_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCreate(cusolverDnHandle_t *handle) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCreate = (cusolverStatus_t (*)(cusolverDnHandle_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCreate");
			fprintf(stderr, "wrapper_cusolverDnCreate:%p\n", wrapper_cusolverDnCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCreate(handle);
		return retval;
	}
}