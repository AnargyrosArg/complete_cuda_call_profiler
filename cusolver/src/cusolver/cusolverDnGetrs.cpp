#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnGetrs)(cusolverDnHandle_t, cusolverDnParams_t, cublasOperation_t, int64_t, int64_t, cudaDataType, const void *, int64_t, const int64_t *, cudaDataType, void *, int64_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnGetrs(cusolverDnHandle_t handle, cusolverDnParams_t params, cublasOperation_t trans, int64_t n, int64_t nrhs, cudaDataType dataTypeA, const void *A, int64_t lda, const int64_t *ipiv, cudaDataType dataTypeB, void *B, int64_t ldb, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnGetrs)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnGetrs = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, cublasOperation_t, int64_t, int64_t, cudaDataType, const void *, int64_t, const int64_t *, cudaDataType, void *, int64_t, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnGetrs");
			fprintf(stderr, "wrapper_cusolverDnGetrs:%p\n", wrapper_cusolverDnGetrs);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnGetrs():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnGetrs(handle, params, trans, n, nrhs, dataTypeA, A, lda, ipiv, dataTypeB, B, ldb, info);
		return retval;
	}
}