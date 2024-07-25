#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSspmv_v2)(cublasHandle_t, cublasFillMode_t, int, const float *, const float *, const float *, int, const float *, float *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSspmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *alpha, const float *AP, const float *x, int incx, const float *beta, float *y, int incy) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSspmv_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSspmv_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const float *, const float *, const float *, int, const float *, float *, int)) dlsym(libwrapper_handle, "wrapper_cublasSspmv_v2");
			fprintf(stderr, "wrapper_cublasSspmv_v2:%p\n", wrapper_cublasSspmv_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSspmv_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSspmv_v2(handle, uplo, n, alpha, AP, x, incx, beta, y, incy);
		return retval;
	}
}