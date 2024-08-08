#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSbsrmv)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, int, const float *, const cusparseMatDescr_t, const float *, const int *, const int *, int, const float *, const float *, float *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSbsrmv(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, int mb, int nb, int nnzb, const float *alpha, const cusparseMatDescr_t descrA, const float *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int blockDim, const float *x, const float *beta, float *y) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSbsrmv)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSbsrmv = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, int, const float *, const cusparseMatDescr_t, const float *, const int *, const int *, int, const float *, const float *, float *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSbsrmv");
			fprintf(stderr, "wrapper_cusparseSbsrmv:%p\n", wrapper_cusparseSbsrmv);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSbsrmv():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSbsrmv(handle, dirA, transA, mb, nb, nnzb, alpha, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, blockDim, x, beta, y);
		return retval;
	}
}