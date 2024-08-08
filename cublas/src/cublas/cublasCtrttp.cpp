#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCtrttp)(cublasHandle_t, cublasFillMode_t, int, const cuComplex *, int, cuComplex *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCtrttp(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuComplex *A, int lda, cuComplex *AP) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCtrttp)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCtrttp = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const cuComplex *, int, cuComplex *)) dlsym(libwrapper_handle, "wrapper_cublasCtrttp");
			fprintf(stderr, "wrapper_cublasCtrttp:%p\n", wrapper_cublasCtrttp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCtrttp():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCtrttp(handle, uplo, n, A, lda, AP);
		return retval;
	}
}