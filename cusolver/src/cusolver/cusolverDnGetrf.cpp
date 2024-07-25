#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnGetrf)(cusolverDnHandle_t, cusolverDnParams_t, int64_t, int64_t, cudaDataType, void *, int64_t, int64_t *, cudaDataType, void *, size_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnGetrf(cusolverDnHandle_t handle, cusolverDnParams_t params, int64_t m, int64_t n, cudaDataType dataTypeA, void *A, int64_t lda, int64_t *ipiv, cudaDataType computeType, void *pBuffer, size_t workspaceInBytes, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnGetrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnGetrf = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, int64_t, int64_t, cudaDataType, void *, int64_t, int64_t *, cudaDataType, void *, size_t, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnGetrf");
			fprintf(stderr, "wrapper_cusolverDnGetrf:%p\n", wrapper_cusolverDnGetrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnGetrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnGetrf(handle, params, m, n, dataTypeA, A, lda, ipiv, computeType, pBuffer, workspaceInBytes, info);
		return retval;
	}
}