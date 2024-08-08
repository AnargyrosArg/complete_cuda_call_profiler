#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDgetrs)(cusolverDnHandle_t, cublasOperation_t, int, int, const double *, int, const int *, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDgetrs(cusolverDnHandle_t handle, cublasOperation_t trans, int n, int nrhs, const double *A, int lda, const int *devIpiv, double *B, int ldb, int *devInfo) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDgetrs)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDgetrs = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasOperation_t, int, int, const double *, int, const int *, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDgetrs");
			fprintf(stderr, "wrapper_cusolverDnDgetrs:%p\n", wrapper_cusolverDnDgetrs);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDgetrs():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDgetrs(handle, trans, n, nrhs, A, lda, devIpiv, B, ldb, devInfo);
		return retval;
	}
}