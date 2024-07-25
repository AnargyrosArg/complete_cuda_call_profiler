#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDsyevdx_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, cusolverEigRange_t, cublasFillMode_t, int, const double *, int, double, double, int, int, int *, const double *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDsyevdx_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cusolverEigRange_t range, cublasFillMode_t uplo, int n, const double *A, int lda, double vl, double vu, int il, int iu, int *meig, const double *W, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDsyevdx_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDsyevdx_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cusolverEigRange_t, cublasFillMode_t, int, const double *, int, double, double, int, int, int *, const double *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDsyevdx_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDsyevdx_bufferSize:%p\n", wrapper_cusolverDnDsyevdx_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDsyevdx_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDsyevdx_bufferSize(handle, jobz, range, uplo, n, A, lda, vl, vu, il, iu, meig, W, lwork);
		return retval;
	}
}