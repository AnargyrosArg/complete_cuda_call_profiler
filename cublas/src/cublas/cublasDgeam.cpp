#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgeam)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, const double *, const double *, int, const double *, const double *, int, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgeam(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, const double *alpha, const double *A, int lda, const double *beta, const double *B, int ldb, double *C, int ldc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgeam)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgeam = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, const double *, const double *, int, const double *, const double *, int, double *, int)) dlsym(libwrapper_handle, "wrapper_cublasDgeam");
			fprintf(stderr, "wrapper_cublasDgeam:%p\n", wrapper_cublasDgeam);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgeam():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgeam(handle, transa, transb, m, n, alpha, A, lda, beta, B, ldb, C, ldc);
		return retval;
	}
}