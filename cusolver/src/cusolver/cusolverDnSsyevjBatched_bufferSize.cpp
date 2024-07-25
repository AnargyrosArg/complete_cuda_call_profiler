#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSsyevjBatched_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const float *, int, const float *, int *, syevjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSsyevjBatched_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const float *A, int lda, const float *W, int *lwork, syevjInfo_t params, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSsyevjBatched_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSsyevjBatched_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const float *, int, const float *, int *, syevjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSsyevjBatched_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSsyevjBatched_bufferSize:%p\n", wrapper_cusolverDnSsyevjBatched_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSsyevjBatched_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSsyevjBatched_bufferSize(handle, jobz, uplo, n, A, lda, W, lwork, params, batchSize);
		return retval;
	}
}