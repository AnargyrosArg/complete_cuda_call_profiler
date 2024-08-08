#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSsytrf)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, int *, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSsytrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, int *ipiv, float *work, int lwork, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSsytrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSsytrf = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, int *, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSsytrf");
			fprintf(stderr, "wrapper_cusolverDnSsytrf:%p\n", wrapper_cusolverDnSsytrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSsytrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSsytrf(handle, uplo, n, A, lda, ipiv, work, lwork, info);
		return retval;
	}
}