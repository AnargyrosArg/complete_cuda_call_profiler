#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCbsrsv2_solve)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, const cuComplex *, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, int, bsrsv2Info_t, const cuComplex *, cuComplex *, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCbsrsv2_solve(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, int mb, int nnzb, const cuComplex *alpha, const cusparseMatDescr_t descrA, const cuComplex *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int blockDim, bsrsv2Info_t info, const cuComplex *f, cuComplex *x, cusparseSolvePolicy_t policy, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCbsrsv2_solve)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCbsrsv2_solve = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, const cuComplex *, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, int, bsrsv2Info_t, const cuComplex *, cuComplex *, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCbsrsv2_solve");
			fprintf(stderr, "wrapper_cusparseCbsrsv2_solve:%p\n", wrapper_cusparseCbsrsv2_solve);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCbsrsv2_solve():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCbsrsv2_solve(handle, dirA, transA, mb, nnzb, alpha, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, blockDim, info, f, x, policy, pBuffer);
		return retval;
	}
}