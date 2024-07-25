#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSyevd)(cusolverDnHandle_t, cusolverDnParams_t, cusolverEigMode_t, cublasFillMode_t, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, cudaDataType, void *, size_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSyevd(cusolverDnHandle_t handle, cusolverDnParams_t params, cusolverEigMode_t jobz, cublasFillMode_t uplo, int64_t n, cudaDataType dataTypeA, void *A, int64_t lda, cudaDataType dataTypeW, void *W, cudaDataType computeType, void *pBuffer, size_t workspaceInBytes, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSyevd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSyevd = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, cusolverEigMode_t, cublasFillMode_t, int64_t, cudaDataType, void *, int64_t, cudaDataType, void *, cudaDataType, void *, size_t, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSyevd");
			fprintf(stderr, "wrapper_cusolverDnSyevd:%p\n", wrapper_cusolverDnSyevd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSyevd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSyevd(handle, params, jobz, uplo, n, dataTypeA, A, lda, dataTypeW, W, computeType, pBuffer, workspaceInBytes, info);
		return retval;
	}
}