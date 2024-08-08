#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSbsrsv2_solve)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, const float *, const cusparseMatDescr_t, const float *, const int *, const int *, int, bsrsv2Info_t, const float *, float *, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSbsrsv2_solve(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, int mb, int nnzb, const float *alpha, const cusparseMatDescr_t descrA, const float *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int blockDim, bsrsv2Info_t info, const float *f, float *x, cusparseSolvePolicy_t policy, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSbsrsv2_solve)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSbsrsv2_solve = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, const float *, const cusparseMatDescr_t, const float *, const int *, const int *, int, bsrsv2Info_t, const float *, float *, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSbsrsv2_solve");
			fprintf(stderr, "wrapper_cusparseSbsrsv2_solve:%p\n", wrapper_cusparseSbsrsv2_solve);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSbsrsv2_solve():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSbsrsv2_solve(handle, dirA, transA, mb, nnzb, alpha, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, blockDim, info, f, x, policy, pBuffer);
		return retval;
	}
}