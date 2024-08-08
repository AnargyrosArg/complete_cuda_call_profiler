#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDsytrf_bufferSize)(cusolverDnHandle_t, int, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDsytrf_bufferSize(cusolverDnHandle_t handle, int n, double *A, int lda, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDsytrf_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDsytrf_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDsytrf_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDsytrf_bufferSize:%p\n", wrapper_cusolverDnDsytrf_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDsytrf_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDsytrf_bufferSize(handle, n, A, lda, lwork);
		return retval;
	}
}