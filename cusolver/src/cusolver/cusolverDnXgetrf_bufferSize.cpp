#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXgetrf_bufferSize)(cusolverDnHandle_t, cusolverDnParams_t, int64_t, int64_t, cudaDataType, const void *, int64_t, cudaDataType, size_t *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXgetrf_bufferSize(cusolverDnHandle_t handle, cusolverDnParams_t params, int64_t m, int64_t n, cudaDataType dataTypeA, const void *A, int64_t lda, cudaDataType computeType, size_t *workspaceInBytesOnDevice, size_t *workspaceInBytesOnHost) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXgetrf_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXgetrf_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, int64_t, int64_t, cudaDataType, const void *, int64_t, cudaDataType, size_t *, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXgetrf_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnXgetrf_bufferSize:%p\n", wrapper_cusolverDnXgetrf_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXgetrf_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXgetrf_bufferSize(handle, params, m, n, dataTypeA, A, lda, computeType, workspaceInBytesOnDevice, workspaceInBytesOnHost);
		return retval;
	}
}