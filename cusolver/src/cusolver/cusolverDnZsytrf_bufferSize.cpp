#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZsytrf_bufferSize)(cusolverDnHandle_t, int, cuDoubleComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZsytrf_bufferSize(cusolverDnHandle_t handle, int n, cuDoubleComplex *A, int lda, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZsytrf_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZsytrf_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, cuDoubleComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZsytrf_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnZsytrf_bufferSize:%p\n", wrapper_cusolverDnZsytrf_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZsytrf_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZsytrf_bufferSize(handle, n, A, lda, lwork);
		return retval;
	}
}