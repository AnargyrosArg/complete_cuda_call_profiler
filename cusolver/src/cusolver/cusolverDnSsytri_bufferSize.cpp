#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSsytri_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, const int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSsytri_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, const int *ipiv, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSsytri_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSsytri_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, const int *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSsytri_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSsytri_bufferSize:%p\n", wrapper_cusolverDnSsytri_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSsytri_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSsytri_bufferSize(handle, uplo, n, A, lda, ipiv, lwork);
		return retval;
	}
}