#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCheevd_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const cuComplex *, int, const float *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCheevd_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const cuComplex *A, int lda, const float *W, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCheevd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCheevd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const cuComplex *, int, const float *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCheevd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnCheevd_bufferSize:%p\n", wrapper_cusolverDnCheevd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCheevd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCheevd_bufferSize(handle, jobz, uplo, n, A, lda, W, lwork);
		return retval;
	}
}