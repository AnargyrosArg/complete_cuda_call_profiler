#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasStpttr)(cublasHandle_t, cublasFillMode_t, int, const float *, float *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasStpttr(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *AP, float *A, int lda) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasStpttr)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasStpttr = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const float *, float *, int)) dlsym(libwrapper_handle, "wrapper_cublasStpttr");
			fprintf(stderr, "wrapper_cublasStpttr:%p\n", wrapper_cublasStpttr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasStpttr():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasStpttr(handle, uplo, n, AP, A, lda);
		return retval;
	}
}