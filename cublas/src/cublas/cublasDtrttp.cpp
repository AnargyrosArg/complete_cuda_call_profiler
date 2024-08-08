#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDtrttp)(cublasHandle_t, cublasFillMode_t, int, const double *, int, double *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDtrttp(cublasHandle_t handle, cublasFillMode_t uplo, int n, const double *A, int lda, double *AP) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDtrttp)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDtrttp = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const double *, int, double *)) dlsym(libwrapper_handle, "wrapper_cublasDtrttp");
			fprintf(stderr, "wrapper_cublasDtrttp:%p\n", wrapper_cublasDtrttp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDtrttp():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDtrttp(handle, uplo, n, A, lda, AP);
		return retval;
	}
}