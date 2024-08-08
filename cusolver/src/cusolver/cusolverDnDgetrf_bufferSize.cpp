#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDgetrf_bufferSize)(cusolverDnHandle_t, int, int, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDgetrf_bufferSize(cusolverDnHandle_t handle, int m, int n, double *A, int lda, int *Lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDgetrf_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDgetrf_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDgetrf_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDgetrf_bufferSize:%p\n", wrapper_cusolverDnDgetrf_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDgetrf_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDgetrf_bufferSize(handle, m, n, A, lda, Lwork);
		return retval;
	}
}