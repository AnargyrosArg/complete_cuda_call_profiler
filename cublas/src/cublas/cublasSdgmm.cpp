#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSdgmm)(cublasHandle_t, cublasSideMode_t, int, int, const float *, int, const float *, int, float *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSdgmm(cublasHandle_t handle, cublasSideMode_t mode, int m, int n, const float *A, int lda, const float *x, int incx, float *C, int ldc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSdgmm)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSdgmm = (cublasStatus_t (*)(cublasHandle_t, cublasSideMode_t, int, int, const float *, int, const float *, int, float *, int)) dlsym(libwrapper_handle, "wrapper_cublasSdgmm");
			fprintf(stderr, "wrapper_cublasSdgmm:%p\n", wrapper_cublasSdgmm);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSdgmm():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSdgmm(handle, mode, m, n, A, lda, x, incx, C, ldc);
		return retval;
	}
}