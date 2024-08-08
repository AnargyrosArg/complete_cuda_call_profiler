#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDsytri)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, const int *, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDsytri(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, const int *ipiv, double *work, int lwork, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDsytri)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDsytri = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, const int *, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDsytri");
			fprintf(stderr, "wrapper_cusolverDnDsytri:%p\n", wrapper_cusolverDnDsytri);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDsytri():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDsytri(handle, uplo, n, A, lda, ipiv, work, lwork, info);
		return retval;
	}
}