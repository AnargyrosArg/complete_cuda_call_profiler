#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDcsrsm2_analysis)(cusparseHandle_t, int, cusparseOperation_t, cusparseOperation_t, int, int, int, const double *, const cusparseMatDescr_t, const double *, const int *, const int *, const double *, int, csrsm2Info_t, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDcsrsm2_analysis(cusparseHandle_t handle, int algo, cusparseOperation_t transA, cusparseOperation_t transB, int m, int nrhs, int nnz, const double *alpha, const cusparseMatDescr_t descrA, const double *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const double *B, int ldb, csrsm2Info_t info, cusparseSolvePolicy_t policy, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDcsrsm2_analysis)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDcsrsm2_analysis = (cusparseStatus_t (*)(cusparseHandle_t, int, cusparseOperation_t, cusparseOperation_t, int, int, int, const double *, const cusparseMatDescr_t, const double *, const int *, const int *, const double *, int, csrsm2Info_t, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDcsrsm2_analysis");
			fprintf(stderr, "wrapper_cusparseDcsrsm2_analysis:%p\n", wrapper_cusparseDcsrsm2_analysis);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDcsrsm2_analysis():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDcsrsm2_analysis(handle, algo, transA, transB, m, nrhs, nnz, alpha, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, B, ldb, info, policy, pBuffer);
		return retval;
	}
}