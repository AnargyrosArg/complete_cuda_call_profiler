#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZpotrsBatched)(cusolverDnHandle_t, cublasFillMode_t, int, int, cuDoubleComplex **, int, cuDoubleComplex **, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZpotrsBatched(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, int nrhs, cuDoubleComplex *A[], int lda, cuDoubleComplex *B[], int ldb, int *d_info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZpotrsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZpotrsBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, int, cuDoubleComplex **, int, cuDoubleComplex **, int, int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZpotrsBatched");
			fprintf(stderr, "wrapper_cusolverDnZpotrsBatched:%p\n", wrapper_cusolverDnZpotrsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZpotrsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, d_info, batchSize);
		return retval;
	}
}