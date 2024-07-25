#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDtpttr)(cublasHandle_t, cublasFillMode_t, int, const double *, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDtpttr(cublasHandle_t handle, cublasFillMode_t uplo, int n, const double *AP, double *A, int lda) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDtpttr)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDtpttr = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const double *, double *, int)) dlsym(libwrapper_handle, "wrapper_cublasDtpttr");
			fprintf(stderr, "wrapper_cublasDtpttr:%p\n", wrapper_cublasDtpttr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDtpttr():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDtpttr(handle, uplo, n, AP, A, lda);
		return retval;
	}
}