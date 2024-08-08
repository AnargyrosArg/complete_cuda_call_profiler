#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsrsv2_solve)(cusparseHandle_t, cusparseOperation_t, int, int, const cuComplex *, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, csrsv2Info_t, const cuComplex *, cuComplex *, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsrsv2_solve(cusparseHandle_t handle, cusparseOperation_t transA, int m, int nnz, const cuComplex *alpha, const cusparseMatDescr_t descrA, const cuComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csrsv2Info_t info, const cuComplex *f, cuComplex *x, cusparseSolvePolicy_t policy, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsrsv2_solve)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsrsv2_solve = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, const cuComplex *, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, csrsv2Info_t, const cuComplex *, cuComplex *, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsrsv2_solve");
			fprintf(stderr, "wrapper_cusparseCcsrsv2_solve:%p\n", wrapper_cusparseCcsrsv2_solve);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsrsv2_solve():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsrsv2_solve(handle, transA, m, nnz, alpha, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, info, f, x, policy, pBuffer);
		return retval;
	}
}