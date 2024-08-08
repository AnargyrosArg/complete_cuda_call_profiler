#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgemmi)(cusparseHandle_t, int, int, int, int, const cuComplex *, const cuComplex *, int, const cuComplex *, const int *, const int *, const cuComplex *, cuComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgemmi(cusparseHandle_t handle, int m, int n, int k, int nnz, const cuComplex *alpha, const cuComplex *A, int lda, const cuComplex *cscValB, const int *cscColPtrB, const int *cscRowIndB, const cuComplex *beta, cuComplex *C, int ldc) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgemmi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgemmi = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, int, const cuComplex *, const cuComplex *, int, const cuComplex *, const int *, const int *, const cuComplex *, cuComplex *, int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgemmi");
			fprintf(stderr, "wrapper_cusparseCgemmi:%p\n", wrapper_cusparseCgemmi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgemmi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgemmi(handle, m, n, k, nnz, alpha, A, lda, cscValB, cscColPtrB, cscRowIndB, beta, C, ldc);
		return retval;
	}
}