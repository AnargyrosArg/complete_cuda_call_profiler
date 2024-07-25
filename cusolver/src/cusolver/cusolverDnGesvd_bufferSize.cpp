#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnGesvd_bufferSize)(cusolverDnHandle_t, cusolverDnParams_t, signed char, signed char, int64_t, int64_t, cudaDataType, const void *, int64_t, cudaDataType, const void *, cudaDataType, const void *, int64_t, cudaDataType, const void *, int64_t, cudaDataType, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnGesvd_bufferSize(cusolverDnHandle_t handle, cusolverDnParams_t params, signed char jobu, signed char jobvt, int64_t m, int64_t n, cudaDataType dataTypeA, const void *A, int64_t lda, cudaDataType dataTypeS, const void *S, cudaDataType dataTypeU, const void *U, int64_t ldu, cudaDataType dataTypeVT, const void *VT, int64_t ldvt, cudaDataType computeType, size_t *workspaceInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnGesvd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnGesvd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, signed char, signed char, int64_t, int64_t, cudaDataType, const void *, int64_t, cudaDataType, const void *, cudaDataType, const void *, int64_t, cudaDataType, const void *, int64_t, cudaDataType, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnGesvd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnGesvd_bufferSize:%p\n", wrapper_cusolverDnGesvd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnGesvd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnGesvd_bufferSize(handle, params, jobu, jobvt, m, n, dataTypeA, A, lda, dataTypeS, S, dataTypeU, U, ldu, dataTypeVT, VT, ldvt, computeType, workspaceInBytes);
		return retval;
	}
}