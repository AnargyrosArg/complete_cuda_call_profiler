#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXgesvdr_bufferSize)(cusolverDnHandle_t, cusolverDnParams_t, signed char, signed char, int64_t, int64_t, int64_t, int64_t, int64_t, cudaDataType, const void *, int64_t, cudaDataType, const void *, cudaDataType, const void *, int64_t, cudaDataType, const void *, int64_t, cudaDataType, size_t *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXgesvdr_bufferSize(cusolverDnHandle_t handle, cusolverDnParams_t params, signed char jobu, signed char jobv, int64_t m, int64_t n, int64_t k, int64_t p, int64_t niters, cudaDataType dataTypeA, const void *A, int64_t lda, cudaDataType dataTypeSrand, const void *Srand, cudaDataType dataTypeUrand, const void *Urand, int64_t ldUrand, cudaDataType dataTypeVrand, const void *Vrand, int64_t ldVrand, cudaDataType computeType, size_t *workspaceInBytesOnDevice, size_t *workspaceInBytesOnHost) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXgesvdr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXgesvdr_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, signed char, signed char, int64_t, int64_t, int64_t, int64_t, int64_t, cudaDataType, const void *, int64_t, cudaDataType, const void *, cudaDataType, const void *, int64_t, cudaDataType, const void *, int64_t, cudaDataType, size_t *, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXgesvdr_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnXgesvdr_bufferSize:%p\n", wrapper_cusolverDnXgesvdr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXgesvdr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXgesvdr_bufferSize(handle, params, jobu, jobv, m, n, k, p, niters, dataTypeA, A, lda, dataTypeSrand, Srand, dataTypeUrand, Urand, ldUrand, dataTypeVrand, Vrand, ldVrand, computeType, workspaceInBytesOnDevice, workspaceInBytesOnHost);
		return retval;
	}
}