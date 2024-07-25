#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSsyr_v2)(cublasHandle_t, cublasFillMode_t, int, const float *, const float *, int, float *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSsyr_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *alpha, const float *x, int incx, float *A, int lda) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSsyr_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSsyr_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const float *, const float *, int, float *, int)) dlsym(libwrapper_handle, "wrapper_cublasSsyr_v2");
			fprintf(stderr, "wrapper_cublasSsyr_v2:%p\n", wrapper_cublasSsyr_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSsyr_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSsyr_v2(handle, uplo, n, alpha, x, incx, A, lda);
		return retval;
	}
}