#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDsyevj)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, double *, int, double *, double *, int, int *, syevjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDsyevj(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, double *A, int lda, double *W, double *work, int lwork, int *info, syevjInfo_t params) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDsyevj)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDsyevj = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, double *, int, double *, double *, int, int *, syevjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDsyevj");
			fprintf(stderr, "wrapper_cusolverDnDsyevj:%p\n", wrapper_cusolverDnDsyevj);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDsyevj():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDsyevj(handle, jobz, uplo, n, A, lda, W, work, lwork, info, params);
		return retval;
	}
}