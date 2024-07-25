#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgemvi)(cusparseHandle_t, cusparseOperation_t, int, int, const double *, const double *, int, int, const double *, const int *, const double *, double *, cusparseIndexBase_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgemvi(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, const double *alpha, const double *A, int lda, int nnz, const double *xVal, const int *xInd, const double *beta, double *y, cusparseIndexBase_t idxBase, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgemvi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgemvi = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, const double *, const double *, int, int, const double *, const int *, const double *, double *, cusparseIndexBase_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgemvi");
			fprintf(stderr, "wrapper_cusparseDgemvi:%p\n", wrapper_cusparseDgemvi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgemvi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgemvi(handle, transA, m, n, alpha, A, lda, nnz, xVal, xInd, beta, y, idxBase, pBuffer);
		return retval;
	}
}