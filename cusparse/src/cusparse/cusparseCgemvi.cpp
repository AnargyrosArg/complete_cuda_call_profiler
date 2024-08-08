#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgemvi)(cusparseHandle_t, cusparseOperation_t, int, int, const cuComplex *, const cuComplex *, int, int, const cuComplex *, const int *, const cuComplex *, cuComplex *, cusparseIndexBase_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgemvi(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, const cuComplex *alpha, const cuComplex *A, int lda, int nnz, const cuComplex *xVal, const int *xInd, const cuComplex *beta, cuComplex *y, cusparseIndexBase_t idxBase, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgemvi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgemvi = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, const cuComplex *, const cuComplex *, int, int, const cuComplex *, const int *, const cuComplex *, cuComplex *, cusparseIndexBase_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgemvi");
			fprintf(stderr, "wrapper_cusparseCgemvi:%p\n", wrapper_cusparseCgemvi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgemvi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgemvi(handle, transA, m, n, alpha, A, lda, nnz, xVal, xInd, beta, y, idxBase, pBuffer);
		return retval;
	}
}