#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDgebrd_bufferSize)(cusolverDnHandle_t, int, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDgebrd_bufferSize(cusolverDnHandle_t handle, int m, int n, int *Lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDgebrd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDgebrd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDgebrd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDgebrd_bufferSize:%p\n", wrapper_cusolverDnDgebrd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDgebrd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDgebrd_bufferSize(handle, m, n, Lwork);
		return retval;
	}
}