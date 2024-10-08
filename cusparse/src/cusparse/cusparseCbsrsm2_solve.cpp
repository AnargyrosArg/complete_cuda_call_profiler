#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCbsrsm2_solve)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, cusparseOperation_t, int, int, int, const cuComplex *, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, int, bsrsm2Info_t, const cuComplex *, int, cuComplex *, int, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCbsrsm2_solve(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, cusparseOperation_t transXY, int mb, int n, int nnzb, const cuComplex *alpha, const cusparseMatDescr_t descrA, const cuComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int blockSize, bsrsm2Info_t info, const cuComplex *B, int ldb, cuComplex *X, int ldx, cusparseSolvePolicy_t policy, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCbsrsm2_solve)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCbsrsm2_solve = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, cusparseOperation_t, int, int, int, const cuComplex *, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, int, bsrsm2Info_t, const cuComplex *, int, cuComplex *, int, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCbsrsm2_solve");
			fprintf(stderr, "wrapper_cusparseCbsrsm2_solve:%p\n", wrapper_cusparseCbsrsm2_solve);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCbsrsm2_solve():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCbsrsm2_solve(handle, dirA, transA, transXY, mb, n, nnzb, alpha, descrA, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, blockSize, info, B, ldb, X, ldx, policy, pBuffer);
		return retval;
	}
}