#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDbsrsv2_analysis)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, int, bsrsv2Info_t, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDbsrsv2_analysis(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, int mb, int nnzb, const cusparseMatDescr_t descrA, const double *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int blockDim, bsrsv2Info_t info, cusparseSolvePolicy_t policy, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDbsrsv2_analysis)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDbsrsv2_analysis = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, int, bsrsv2Info_t, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDbsrsv2_analysis");
			fprintf(stderr, "wrapper_cusparseDbsrsv2_analysis:%p\n", wrapper_cusparseDbsrsv2_analysis);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDbsrsv2_analysis():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDbsrsv2_analysis(handle, dirA, transA, mb, nnzb, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, blockDim, info, policy, pBuffer);
		return retval;
	}
}