#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZbsric02_bufferSize)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, cuDoubleComplex *, const int *, const int *, int, bsric02Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZbsric02_bufferSize(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nnzb, const cusparseMatDescr_t descrA, cuDoubleComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int blockDim, bsric02Info_t info, int *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZbsric02_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZbsric02_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, cuDoubleComplex *, const int *, const int *, int, bsric02Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZbsric02_bufferSize");
			fprintf(stderr, "wrapper_cusparseZbsric02_bufferSize:%p\n", wrapper_cusparseZbsric02_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZbsric02_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZbsric02_bufferSize(handle, dirA, mb, nnzb, descrA, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, blockDim, info, pBufferSizeInBytes);
		return retval;
	}
}