#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZtpttr)(cublasHandle_t, cublasFillMode_t, int, const cuDoubleComplex *, cuDoubleComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZtpttr(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuDoubleComplex *AP, cuDoubleComplex *A, int lda) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZtpttr)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZtpttr = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const cuDoubleComplex *, cuDoubleComplex *, int)) dlsym(libwrapper_handle, "wrapper_cublasZtpttr");
			fprintf(stderr, "wrapper_cublasZtpttr:%p\n", wrapper_cublasZtpttr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZtpttr():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZtpttr(handle, uplo, n, AP, A, lda);
		return retval;
	}
}