#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCsytrf_bufferSize)(cusolverDnHandle_t, int, cuComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCsytrf_bufferSize(cusolverDnHandle_t handle, int n, cuComplex *A, int lda, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCsytrf_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCsytrf_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, cuComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCsytrf_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnCsytrf_bufferSize:%p\n", wrapper_cusolverDnCsytrf_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCsytrf_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCsytrf_bufferSize(handle, n, A, lda, lwork);
		return retval;
	}
}