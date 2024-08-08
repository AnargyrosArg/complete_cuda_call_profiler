#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgemmi)(cusparseHandle_t, int, int, int, int, const cuDoubleComplex *, const cuDoubleComplex *, int, const cuDoubleComplex *, const int *, const int *, const cuDoubleComplex *, cuDoubleComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgemmi(cusparseHandle_t handle, int m, int n, int k, int nnz, const cuDoubleComplex *alpha, const cuDoubleComplex *A, int lda, const cuDoubleComplex *cscValB, const int *cscColPtrB, const int *cscRowIndB, const cuDoubleComplex *beta, cuDoubleComplex *C, int ldc) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgemmi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgemmi = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, int, const cuDoubleComplex *, const cuDoubleComplex *, int, const cuDoubleComplex *, const int *, const int *, const cuDoubleComplex *, cuDoubleComplex *, int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgemmi");
			fprintf(stderr, "wrapper_cusparseZgemmi:%p\n", wrapper_cusparseZgemmi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgemmi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgemmi(handle, m, n, k, nnz, alpha, A, lda, cscValB, cscColPtrB, cscRowIndB, beta, C, ldc);
		return retval;
	}
}