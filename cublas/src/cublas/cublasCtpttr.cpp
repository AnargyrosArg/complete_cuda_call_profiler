#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCtpttr)(cublasHandle_t, cublasFillMode_t, int, const cuComplex *, cuComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCtpttr(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuComplex *AP, cuComplex *A, int lda) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCtpttr)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCtpttr = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const cuComplex *, cuComplex *, int)) dlsym(libwrapper_handle, "wrapper_cublasCtpttr");
			fprintf(stderr, "wrapper_cublasCtpttr:%p\n", wrapper_cublasCtpttr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCtpttr():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCtpttr(handle, uplo, n, AP, A, lda);
		return retval;
	}
}