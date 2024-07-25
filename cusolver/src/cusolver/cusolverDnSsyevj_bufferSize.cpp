#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSsyevj_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const float *, int, const float *, int *, syevjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSsyevj_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const float *A, int lda, const float *W, int *lwork, syevjInfo_t params) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSsyevj_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSsyevj_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const float *, int, const float *, int *, syevjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSsyevj_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSsyevj_bufferSize:%p\n", wrapper_cusolverDnSsyevj_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSsyevj_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSsyevj_bufferSize(handle, jobz, uplo, n, A, lda, W, lwork, params);
		return retval;
	}
}