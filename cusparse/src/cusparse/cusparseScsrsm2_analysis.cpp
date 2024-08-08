#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsrsm2_analysis)(cusparseHandle_t, int, cusparseOperation_t, cusparseOperation_t, int, int, int, const float *, const cusparseMatDescr_t, const float *, const int *, const int *, const float *, int, csrsm2Info_t, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsrsm2_analysis(cusparseHandle_t handle, int algo, cusparseOperation_t transA, cusparseOperation_t transB, int m, int nrhs, int nnz, const float *alpha, const cusparseMatDescr_t descrA, const float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const float *B, int ldb, csrsm2Info_t info, cusparseSolvePolicy_t policy, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsrsm2_analysis)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsrsm2_analysis = (cusparseStatus_t (*)(cusparseHandle_t, int, cusparseOperation_t, cusparseOperation_t, int, int, int, const float *, const cusparseMatDescr_t, const float *, const int *, const int *, const float *, int, csrsm2Info_t, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsrsm2_analysis");
			fprintf(stderr, "wrapper_cusparseScsrsm2_analysis:%p\n", wrapper_cusparseScsrsm2_analysis);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsrsm2_analysis():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsrsm2_analysis(handle, algo, transA, transB, m, nrhs, nnz, alpha, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, B, ldb, info, policy, pBuffer);
		return retval;
	}
}