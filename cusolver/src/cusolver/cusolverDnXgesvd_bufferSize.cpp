#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXgesvd_bufferSize)(cusolverDnHandle_t, cusolverDnParams_t, signed char, signed char, int64_t, int64_t, cudaDataType, const void *, int64_t, cudaDataType, const void *, cudaDataType, const void *, int64_t, cudaDataType, const void *, int64_t, cudaDataType, size_t *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXgesvd_bufferSize(cusolverDnHandle_t handle, cusolverDnParams_t params, signed char jobu, signed char jobvt, int64_t m, int64_t n, cudaDataType dataTypeA, const void *A, int64_t lda, cudaDataType dataTypeS, const void *S, cudaDataType dataTypeU, const void *U, int64_t ldu, cudaDataType dataTypeVT, const void *VT, int64_t ldvt, cudaDataType computeType, size_t *workspaceInBytesOnDevice, size_t *workspaceInBytesOnHost) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXgesvd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXgesvd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, signed char, signed char, int64_t, int64_t, cudaDataType, const void *, int64_t, cudaDataType, const void *, cudaDataType, const void *, int64_t, cudaDataType, const void *, int64_t, cudaDataType, size_t *, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXgesvd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnXgesvd_bufferSize:%p\n", wrapper_cusolverDnXgesvd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXgesvd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXgesvd_bufferSize(handle, params, jobu, jobvt, m, n, dataTypeA, A, lda, dataTypeS, S, dataTypeU, U, ldu, dataTypeVT, VT, ldvt, computeType, workspaceInBytesOnDevice, workspaceInBytesOnHost);
		return retval;
	}
}