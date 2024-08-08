#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCgeqrf_bufferSize)(cusolverDnHandle_t, int, int, cuComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCgeqrf_bufferSize(cusolverDnHandle_t handle, int m, int n, cuComplex *A, int lda, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCgeqrf_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCgeqrf_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, cuComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCgeqrf_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnCgeqrf_bufferSize:%p\n", wrapper_cusolverDnCgeqrf_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCgeqrf_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCgeqrf_bufferSize(handle, m, n, A, lda, lwork);
		return retval;
	}
}