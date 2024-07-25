#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCsytri)(cusolverDnHandle_t, cublasFillMode_t, int, cuComplex *, int, const int *, cuComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCsytri(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *A, int lda, const int *ipiv, cuComplex *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCsytri)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCsytri = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, cuComplex *, int, const int *, cuComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCsytri");
			fprintf(stderr, "wrapper_cusolverDnCsytri:%p\n", wrapper_cusolverDnCsytri);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCsytri():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCsytri(handle, uplo, n, A, lda, ipiv, work, lwork, info);
		return retval;
	}
}