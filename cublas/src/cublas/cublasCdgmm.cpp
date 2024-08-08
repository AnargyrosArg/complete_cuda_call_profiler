#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCdgmm)(cublasHandle_t, cublasSideMode_t, int, int, const cuComplex *, int, const cuComplex *, int, cuComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCdgmm(cublasHandle_t handle, cublasSideMode_t mode, int m, int n, const cuComplex *A, int lda, const cuComplex *x, int incx, cuComplex *C, int ldc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCdgmm)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCdgmm = (cublasStatus_t (*)(cublasHandle_t, cublasSideMode_t, int, int, const cuComplex *, int, const cuComplex *, int, cuComplex *, int)) dlsym(libwrapper_handle, "wrapper_cublasCdgmm");
			fprintf(stderr, "wrapper_cublasCdgmm:%p\n", wrapper_cublasCdgmm);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCdgmm():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCdgmm(handle, mode, m, n, A, lda, x, incx, C, ldc);
		return retval;
	}
}