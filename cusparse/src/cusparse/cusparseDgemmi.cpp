#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgemmi)(cusparseHandle_t, int, int, int, int, const double *, const double *, int, const double *, const int *, const int *, const double *, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgemmi(cusparseHandle_t handle, int m, int n, int k, int nnz, const double *alpha, const double *A, int lda, const double *cscValB, const int *cscColPtrB, const int *cscRowIndB, const double *beta, double *C, int ldc) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgemmi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgemmi = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, int, const double *, const double *, int, const double *, const int *, const int *, const double *, double *, int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgemmi");
			fprintf(stderr, "wrapper_cusparseDgemmi:%p\n", wrapper_cusparseDgemmi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgemmi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgemmi(handle, m, n, k, nnz, alpha, A, lda, cscValB, cscColPtrB, cscRowIndB, beta, C, ldc);
		return retval;
	}
}