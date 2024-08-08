#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasStrttp)(cublasHandle_t, cublasFillMode_t, int, const float *, int, float *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasStrttp(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *A, int lda, float *AP) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasStrttp)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasStrttp = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const float *, int, float *)) dlsym(libwrapper_handle, "wrapper_cublasStrttp");
			fprintf(stderr, "wrapper_cublasStrttp:%p\n", wrapper_cublasStrttp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasStrttp():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasStrttp(handle, uplo, n, A, lda, AP);
		return retval;
	}
}