#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgemmBatched)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const double *, const double * const *, int, const double * const *, int, const double *, double * const *, int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgemmBatched(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const double *alpha, const double * const Aarray[], int lda, const double * const Barray[], int ldb, const double *beta, double * const Carray[], int ldc, int batchCount) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgemmBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgemmBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const double *, const double * const *, int, const double * const *, int, const double *, double * const *, int, int)) dlsym(libwrapper_handle, "wrapper_cublasDgemmBatched");
			fprintf(stderr, "wrapper_cublasDgemmBatched:%p\n", wrapper_cublasDgemmBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgemmBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgemmBatched(handle, transa, transb, m, n, k, alpha, Aarray, lda, Barray, ldb, beta, Carray, ldc, batchCount);
		return retval;
	}
}