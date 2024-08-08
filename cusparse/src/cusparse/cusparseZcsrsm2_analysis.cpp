#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZcsrsm2_analysis)(cusparseHandle_t, int, cusparseOperation_t, cusparseOperation_t, int, int, int, const cuDoubleComplex *, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, const cuDoubleComplex *, int, csrsm2Info_t, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZcsrsm2_analysis(cusparseHandle_t handle, int algo, cusparseOperation_t transA, cusparseOperation_t transB, int m, int nrhs, int nnz, const cuDoubleComplex *alpha, const cusparseMatDescr_t descrA, const cuDoubleComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cuDoubleComplex *B, int ldb, csrsm2Info_t info, cusparseSolvePolicy_t policy, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZcsrsm2_analysis)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZcsrsm2_analysis = (cusparseStatus_t (*)(cusparseHandle_t, int, cusparseOperation_t, cusparseOperation_t, int, int, int, const cuDoubleComplex *, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, const cuDoubleComplex *, int, csrsm2Info_t, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZcsrsm2_analysis");
			fprintf(stderr, "wrapper_cusparseZcsrsm2_analysis:%p\n", wrapper_cusparseZcsrsm2_analysis);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZcsrsm2_analysis():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZcsrsm2_analysis(handle, algo, transA, transB, m, nrhs, nnz, alpha, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, B, ldb, info, policy, pBuffer);
		return retval;
	}
}