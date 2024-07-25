#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDpotri_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDpotri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDpotri_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDpotri_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDpotri_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDpotri_bufferSize:%p\n", wrapper_cusolverDnDpotri_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDpotri_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDpotri_bufferSize(handle, uplo, n, A, lda, lwork);
		return retval;
	}
}