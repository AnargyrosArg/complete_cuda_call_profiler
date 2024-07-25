#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZtrmm_v2)(cublasHandle_t, cublasSideMode_t, cublasFillMode_t, cublasOperation_t, cublasDiagType_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, int, const cuDoubleComplex *, int, cuDoubleComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZtrmm_v2(cublasHandle_t handle, cublasSideMode_t side, cublasFillMode_t uplo, cublasOperation_t trans, cublasDiagType_t diag, int m, int n, const cuDoubleComplex *alpha, const cuDoubleComplex *A, int lda, const cuDoubleComplex *B, int ldb, cuDoubleComplex *C, int ldc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZtrmm_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZtrmm_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasSideMode_t, cublasFillMode_t, cublasOperation_t, cublasDiagType_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, int, const cuDoubleComplex *, int, cuDoubleComplex *, int)) dlsym(libwrapper_handle, "wrapper_cublasZtrmm_v2");
			fprintf(stderr, "wrapper_cublasZtrmm_v2:%p\n", wrapper_cublasZtrmm_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZtrmm_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZtrmm_v2(handle, side, uplo, trans, diag, m, n, alpha, A, lda, B, ldb, C, ldc);
		return retval;
	}
}