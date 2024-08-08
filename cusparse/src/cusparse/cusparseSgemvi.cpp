#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgemvi)(cusparseHandle_t, cusparseOperation_t, int, int, const float *, const float *, int, int, const float *, const int *, const float *, float *, cusparseIndexBase_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgemvi(cusparseHandle_t handle, cusparseOperation_t transA, int m, int n, const float *alpha, const float *A, int lda, int nnz, const float *xVal, const int *xInd, const float *beta, float *y, cusparseIndexBase_t idxBase, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgemvi)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgemvi = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, const float *, const float *, int, int, const float *, const int *, const float *, float *, cusparseIndexBase_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgemvi");
			fprintf(stderr, "wrapper_cusparseSgemvi:%p\n", wrapper_cusparseSgemvi);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgemvi():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgemvi(handle, transA, m, n, alpha, A, lda, nnz, xVal, xInd, beta, y, idxBase, pBuffer);
		return retval;
	}
}