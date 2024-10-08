#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZbsric02_analysis)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, int, bsric02Info_t, cusparseSolvePolicy_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZbsric02_analysis(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nnzb, const cusparseMatDescr_t descrA, const cuDoubleComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int blockDim, bsric02Info_t info, cusparseSolvePolicy_t policy, void *pInputBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZbsric02_analysis)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZbsric02_analysis = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, int, bsric02Info_t, cusparseSolvePolicy_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZbsric02_analysis");
			fprintf(stderr, "wrapper_cusparseZbsric02_analysis:%p\n", wrapper_cusparseZbsric02_analysis);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZbsric02_analysis():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZbsric02_analysis(handle, dirA, mb, nnzb, descrA, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, blockDim, info, policy, pInputBuffer);
		return retval;
	}
}