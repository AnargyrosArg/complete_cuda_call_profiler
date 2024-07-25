#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZtrttp)(cublasHandle_t, cublasFillMode_t, int, const cuDoubleComplex *, int, cuDoubleComplex *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZtrttp(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuDoubleComplex *A, int lda, cuDoubleComplex *AP) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZtrttp)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZtrttp = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const cuDoubleComplex *, int, cuDoubleComplex *)) dlsym(libwrapper_handle, "wrapper_cublasZtrttp");
			fprintf(stderr, "wrapper_cublasZtrttp:%p\n", wrapper_cublasZtrttp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZtrttp():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZtrttp(handle, uplo, n, A, lda, AP);
		return retval;
	}
}