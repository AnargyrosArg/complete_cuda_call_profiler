#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgemmi)(cusparseHandle_t, int, int, int, int, const float *, const float *, int, const float *, const int *, const int *, const float *, float *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgemmi(cusparseHandle_t handle, int m, int n, int k, int nnz, const float *alpha, const float *A, int lda, const float *cscValB, const int *cscColPtrB, const int *cscRowIndB, const float *beta, float *C, int ldc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgemmi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgemmi = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, int, const float *, const float *, int, const float *, const int *, const int *, const float *, float *, int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgemmi");
			fprintf(stderr, "wrapper_cusparseSgemmi:%p\n", wrapper_cusparseSgemmi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgemmi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgemmi(handle, m, n, k, nnz, alpha, A, lda, cscValB, cscColPtrB, cscRowIndB, beta, C, ldc);
		return retval;
	}
}