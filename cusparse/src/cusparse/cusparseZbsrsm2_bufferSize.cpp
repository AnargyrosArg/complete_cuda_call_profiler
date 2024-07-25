#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZbsrsm2_bufferSize)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, cusparseOperation_t, int, int, int, const cusparseMatDescr_t, cuDoubleComplex *, const int *, const int *, int, bsrsm2Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZbsrsm2_bufferSize(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, cusparseOperation_t transXY, int mb, int n, int nnzb, const cusparseMatDescr_t descrA, cuDoubleComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int blockSize, bsrsm2Info_t info, int *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZbsrsm2_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZbsrsm2_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, cusparseOperation_t, int, int, int, const cusparseMatDescr_t, cuDoubleComplex *, const int *, const int *, int, bsrsm2Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZbsrsm2_bufferSize");
			fprintf(stderr, "wrapper_cusparseZbsrsm2_bufferSize:%p\n", wrapper_cusparseZbsrsm2_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZbsrsm2_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZbsrsm2_bufferSize(handle, dirA, transA, transXY, mb, n, nnzb, descrA, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, blockSize, info, pBufferSizeInBytes);
		return retval;
	}
}