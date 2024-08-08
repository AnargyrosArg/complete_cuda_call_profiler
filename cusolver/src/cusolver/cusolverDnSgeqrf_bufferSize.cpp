#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSgeqrf_bufferSize)(cusolverDnHandle_t, int, int, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSgeqrf_bufferSize(cusolverDnHandle_t handle, int m, int n, float *A, int lda, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSgeqrf_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSgeqrf_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSgeqrf_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSgeqrf_bufferSize:%p\n", wrapper_cusolverDnSgeqrf_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSgeqrf_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSgeqrf_bufferSize(handle, m, n, A, lda, lwork);
		return retval;
	}
}