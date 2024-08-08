#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSgetrs)(cusolverDnHandle_t, cublasOperation_t, int, int, const float *, int, const int *, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSgetrs(cusolverDnHandle_t handle, cublasOperation_t trans, int n, int nrhs, const float *A, int lda, const int *devIpiv, float *B, int ldb, int *devInfo) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSgetrs)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSgetrs = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasOperation_t, int, int, const float *, int, const int *, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSgetrs");
			fprintf(stderr, "wrapper_cusolverDnSgetrs:%p\n", wrapper_cusolverDnSgetrs);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSgetrs():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSgetrs(handle, trans, n, nrhs, A, lda, devIpiv, B, ldb, devInfo);
		return retval;
	}
}