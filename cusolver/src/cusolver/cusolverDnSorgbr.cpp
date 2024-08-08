#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSorgbr)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, float *, int, const float *, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSorgbr(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, float *A, int lda, const float *tau, float *work, int lwork, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSorgbr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSorgbr = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, float *, int, const float *, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSorgbr");
			fprintf(stderr, "wrapper_cusolverDnSorgbr:%p\n", wrapper_cusolverDnSorgbr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSorgbr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSorgbr(handle, side, m, n, k, A, lda, tau, work, lwork, info);
		return retval;
	}
}