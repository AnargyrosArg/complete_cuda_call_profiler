#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDdgmm)(cublasHandle_t, cublasSideMode_t, int, int, const double *, int, const double *, int, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDdgmm(cublasHandle_t handle, cublasSideMode_t mode, int m, int n, const double *A, int lda, const double *x, int incx, double *C, int ldc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDdgmm)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDdgmm = (cublasStatus_t (*)(cublasHandle_t, cublasSideMode_t, int, int, const double *, int, const double *, int, double *, int)) dlsym(libwrapper_handle, "wrapper_cublasDdgmm");
			fprintf(stderr, "wrapper_cublasDdgmm:%p\n", wrapper_cublasDdgmm);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDdgmm():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDdgmm(handle, mode, m, n, A, lda, x, incx, C, ldc);
		return retval;
	}
}