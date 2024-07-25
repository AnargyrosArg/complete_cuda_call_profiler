#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnPotrs)(cusolverDnHandle_t, cusolverDnParams_t, cublasFillMode_t, int64_t, int64_t, cudaDataType, const void *, int64_t, cudaDataType, void *, int64_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnPotrs(cusolverDnHandle_t handle, cusolverDnParams_t params, cublasFillMode_t uplo, int64_t n, int64_t nrhs, cudaDataType dataTypeA, const void *A, int64_t lda, cudaDataType dataTypeB, void *B, int64_t ldb, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnPotrs)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnPotrs = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnParams_t, cublasFillMode_t, int64_t, int64_t, cudaDataType, const void *, int64_t, cudaDataType, void *, int64_t, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnPotrs");
			fprintf(stderr, "wrapper_cusolverDnPotrs:%p\n", wrapper_cusolverDnPotrs);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnPotrs():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnPotrs(handle, params, uplo, n, nrhs, dataTypeA, A, lda, dataTypeB, B, ldb, info);
		return retval;
	}
}