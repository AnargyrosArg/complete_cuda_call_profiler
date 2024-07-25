#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasChpmv_v2)(cublasHandle_t, cublasFillMode_t, int, const cuComplex *, const cuComplex *, const cuComplex *, int, const cuComplex *, cuComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasChpmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuComplex *alpha, const cuComplex *AP, const cuComplex *x, int incx, const cuComplex *beta, cuComplex *y, int incy) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasChpmv_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasChpmv_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const cuComplex *, const cuComplex *, const cuComplex *, int, const cuComplex *, cuComplex *, int)) dlsym(libwrapper_handle, "wrapper_cublasChpmv_v2");
			fprintf(stderr, "wrapper_cublasChpmv_v2:%p\n", wrapper_cublasChpmv_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasChpmv_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasChpmv_v2(handle, uplo, n, alpha, AP, x, incx, beta, y, incy);
		return retval;
	}
}