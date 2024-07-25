#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCpotrsBatched)(cusolverDnHandle_t, cublasFillMode_t, int, int, cuComplex **, int, cuComplex **, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCpotrsBatched(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, int nrhs, cuComplex *A[], int lda, cuComplex *B[], int ldb, int *d_info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCpotrsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCpotrsBatched = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, int, cuComplex **, int, cuComplex **, int, int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCpotrsBatched");
			fprintf(stderr, "wrapper_cusolverDnCpotrsBatched:%p\n", wrapper_cusolverDnCpotrsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCpotrsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, d_info, batchSize);
		return retval;
	}
}