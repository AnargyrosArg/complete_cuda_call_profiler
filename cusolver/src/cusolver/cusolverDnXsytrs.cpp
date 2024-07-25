#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXsytrs)(cusolverDnHandle_t, cublasFillMode_t, int64_t, int64_t, cudaDataType, const void *, int64_t, const int64_t *, cudaDataType, void *, int64_t, void *, size_t, void *, size_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXsytrs(cusolverDnHandle_t handle, cublasFillMode_t uplo, int64_t n, int64_t nrhs, cudaDataType dataTypeA, const void *A, int64_t lda, const int64_t *ipiv, cudaDataType dataTypeB, void *B, int64_t ldb, void *bufferOnDevice, size_t workspaceInBytesOnDevice, void *bufferOnHost, size_t workspaceInBytesOnHost, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXsytrs)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXsytrs = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int64_t, int64_t, cudaDataType, const void *, int64_t, const int64_t *, cudaDataType, void *, int64_t, void *, size_t, void *, size_t, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXsytrs");
			fprintf(stderr, "wrapper_cusolverDnXsytrs:%p\n", wrapper_cusolverDnXsytrs);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXsytrs():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXsytrs(handle, uplo, n, nrhs, dataTypeA, A, lda, ipiv, dataTypeB, B, ldb, bufferOnDevice, workspaceInBytesOnDevice, bufferOnHost, workspaceInBytesOnHost, info);
		return retval;
	}
}