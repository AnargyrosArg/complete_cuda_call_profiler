#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZheevd_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const cuDoubleComplex *, int, const double *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZheevd_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const cuDoubleComplex *A, int lda, const double *W, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZheevd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZheevd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const cuDoubleComplex *, int, const double *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZheevd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnZheevd_bufferSize:%p\n", wrapper_cusolverDnZheevd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZheevd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZheevd_bufferSize(handle, jobz, uplo, n, A, lda, W, lwork);
		return retval;
	}
}