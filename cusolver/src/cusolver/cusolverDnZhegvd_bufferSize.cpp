#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZhegvd_bufferSize)(cusolverDnHandle_t, cusolverEigType_t, cusolverEigMode_t, cublasFillMode_t, int, const cuDoubleComplex *, int, const cuDoubleComplex *, int, const double *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZhegvd_bufferSize(cusolverDnHandle_t handle, cusolverEigType_t itype, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const cuDoubleComplex *A, int lda, const cuDoubleComplex *B, int ldb, const double *W, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZhegvd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZhegvd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigType_t, cusolverEigMode_t, cublasFillMode_t, int, const cuDoubleComplex *, int, const cuDoubleComplex *, int, const double *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZhegvd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnZhegvd_bufferSize:%p\n", wrapper_cusolverDnZhegvd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZhegvd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZhegvd_bufferSize(handle, itype, jobz, uplo, n, A, lda, B, ldb, W, lwork);
		return retval;
	}
}