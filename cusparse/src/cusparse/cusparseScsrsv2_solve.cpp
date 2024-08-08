#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsrsv2_solve)(cusparseHandle_t, cusparseOperation_t, int, int, const float *, const cusparseMatDescr_t, const float *, const int *, const int *, csrsv2Info_t, const float *, float *, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsrsv2_solve(cusparseHandle_t handle, cusparseOperation_t transA, int m, int nnz, const float *alpha, const cusparseMatDescr_t descrA, const float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csrsv2Info_t info, const float *f, float *x, cusparseSolvePolicy_t policy, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsrsv2_solve)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsrsv2_solve = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, const float *, const cusparseMatDescr_t, const float *, const int *, const int *, csrsv2Info_t, const float *, float *, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsrsv2_solve");
			fprintf(stderr, "wrapper_cusparseScsrsv2_solve:%p\n", wrapper_cusparseScsrsv2_solve);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsrsv2_solve():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsrsv2_solve(handle, transA, m, nnz, alpha, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, info, f, x, policy, pBuffer);
		return retval;
	}
}