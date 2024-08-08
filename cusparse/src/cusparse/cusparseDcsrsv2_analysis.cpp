#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDcsrsv2_analysis)(cusparseHandle_t, cusparseOperation_t, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, csrsv2Info_t, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDcsrsv2_analysis(cusparseHandle_t handle, cusparseOperation_t transA, int m, int nnz, const cusparseMatDescr_t descrA, const double *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csrsv2Info_t info, cusparseSolvePolicy_t policy, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDcsrsv2_analysis)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDcsrsv2_analysis = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, csrsv2Info_t, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDcsrsv2_analysis");
			fprintf(stderr, "wrapper_cusparseDcsrsv2_analysis:%p\n", wrapper_cusparseDcsrsv2_analysis);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDcsrsv2_analysis():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDcsrsv2_analysis(handle, transA, m, nnz, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, info, policy, pBuffer);
		return retval;
	}
}