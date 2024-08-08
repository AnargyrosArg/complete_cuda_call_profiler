#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDorgbr)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, double *, int, const double *, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDorgbr(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, double *A, int lda, const double *tau, double *work, int lwork, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDorgbr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDorgbr = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, double *, int, const double *, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDorgbr");
			fprintf(stderr, "wrapper_cusolverDnDorgbr:%p\n", wrapper_cusolverDnDorgbr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDorgbr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDorgbr(handle, side, m, n, k, A, lda, tau, work, lwork, info);
		return retval;
	}
}