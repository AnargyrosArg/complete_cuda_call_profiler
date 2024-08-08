#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZbsrsm2_solve)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, cusparseOperation_t, int, int, int, const cuDoubleComplex *, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, int, bsrsm2Info_t, const cuDoubleComplex *, int, cuDoubleComplex *, int, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZbsrsm2_solve(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, cusparseOperation_t transXY, int mb, int n, int nnzb, const cuDoubleComplex *alpha, const cusparseMatDescr_t descrA, const cuDoubleComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int blockSize, bsrsm2Info_t info, const cuDoubleComplex *B, int ldb, cuDoubleComplex *X, int ldx, cusparseSolvePolicy_t policy, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZbsrsm2_solve)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZbsrsm2_solve = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, cusparseOperation_t, int, int, int, const cuDoubleComplex *, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, int, bsrsm2Info_t, const cuDoubleComplex *, int, cuDoubleComplex *, int, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZbsrsm2_solve");
			fprintf(stderr, "wrapper_cusparseZbsrsm2_solve:%p\n", wrapper_cusparseZbsrsm2_solve);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZbsrsm2_solve():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZbsrsm2_solve(handle, dirA, transA, transXY, mb, n, nnzb, alpha, descrA, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, blockSize, info, B, ldb, X, ldx, policy, pBuffer);
		return retval;
	}
}