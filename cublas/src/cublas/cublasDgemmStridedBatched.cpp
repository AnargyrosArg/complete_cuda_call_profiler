#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgemmStridedBatched)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const double *, const double *, int, long long int, const double *, int, long long int, const double *, double *, int, long long int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgemmStridedBatched(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const double *alpha, const double *A, int lda, long long int strideA, const double *B, int ldb, long long int strideB, const double *beta, double *C, int ldc, long long int strideC, int batchCount) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgemmStridedBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgemmStridedBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const double *, const double *, int, long long int, const double *, int, long long int, const double *, double *, int, long long int, int)) dlsym(libwrapper_handle, "wrapper_cublasDgemmStridedBatched");
			fprintf(stderr, "wrapper_cublasDgemmStridedBatched:%p\n", wrapper_cublasDgemmStridedBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgemmStridedBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgemmStridedBatched(handle, transa, transb, m, n, k, alpha, A, lda, strideA, B, ldb, strideB, beta, C, ldc, strideC, batchCount);
		return retval;
	}
}