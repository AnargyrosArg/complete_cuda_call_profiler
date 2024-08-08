#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXsytrs_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int64_t, int64_t, cudaDataType, const void *, int64_t, const int64_t *, cudaDataType, void *, int64_t, size_t *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXsytrs_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int64_t n, int64_t nrhs, cudaDataType dataTypeA, const void *A, int64_t lda, const int64_t *ipiv, cudaDataType dataTypeB, void *B, int64_t ldb, size_t *workspaceInBytesOnDevice, size_t *workspaceInBytesOnHost) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXsytrs_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXsytrs_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int64_t, int64_t, cudaDataType, const void *, int64_t, const int64_t *, cudaDataType, void *, int64_t, size_t *, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXsytrs_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnXsytrs_bufferSize:%p\n", wrapper_cusolverDnXsytrs_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXsytrs_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXsytrs_bufferSize(handle, uplo, n, nrhs, dataTypeA, A, lda, ipiv, dataTypeB, B, ldb, workspaceInBytesOnDevice, workspaceInBytesOnHost);
		return retval;
	}
}