#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZungbr)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, cuDoubleComplex *, int, const cuDoubleComplex *, cuDoubleComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZungbr(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, cuDoubleComplex *A, int lda, const cuDoubleComplex *tau, cuDoubleComplex *work, int lwork, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZungbr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZungbr = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, cuDoubleComplex *, int, const cuDoubleComplex *, cuDoubleComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZungbr");
			fprintf(stderr, "wrapper_cusolverDnZungbr:%p\n", wrapper_cusolverDnZungbr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZungbr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZungbr(handle, side, m, n, k, A, lda, tau, work, lwork, info);
		return retval;
	}
}