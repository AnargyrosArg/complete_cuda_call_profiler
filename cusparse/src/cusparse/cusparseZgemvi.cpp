#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgemvi)(cusparseHandle_t, cusparseOperation_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, int, int, const cuDoubleComplex *, const int *, const cuDoubleComplex *, cuDoubleComplex *, cusparseIndexBase_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgemvi(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, const cuDoubleComplex *alpha, const cuDoubleComplex *A, int lda, int nnz, const cuDoubleComplex *xVal, const int *xInd, const cuDoubleComplex *beta, cuDoubleComplex *y, cusparseIndexBase_t idxBase, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgemvi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgemvi = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, int, int, const cuDoubleComplex *, const int *, const cuDoubleComplex *, cuDoubleComplex *, cusparseIndexBase_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgemvi");
			fprintf(stderr, "wrapper_cusparseZgemvi:%p\n", wrapper_cusparseZgemvi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgemvi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgemvi(handle, transA, m, n, alpha, A, lda, nnz, xVal, xInd, beta, y, idxBase, pBuffer);
		return retval;
	}
}