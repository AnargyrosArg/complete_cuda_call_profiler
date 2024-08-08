#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZsytri_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int, cuDoubleComplex *, int, const int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZsytri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, const int *ipiv, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZsytri_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZsytri_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, cuDoubleComplex *, int, const int *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZsytri_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnZsytri_bufferSize:%p\n", wrapper_cusolverDnZsytri_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZsytri_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZsytri_bufferSize(handle, uplo, n, A, lda, ipiv, lwork);
		return retval;
	}
}