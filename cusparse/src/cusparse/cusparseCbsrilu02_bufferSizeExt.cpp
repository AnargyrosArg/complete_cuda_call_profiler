#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCbsrilu02_bufferSizeExt)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, cuComplex *, const int *, const int *, int, bsrilu02Info_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCbsrilu02_bufferSizeExt(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nnzb, const cusparseMatDescr_t descrA, cuComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int blockSize, bsrilu02Info_t info, size_t *pBufferSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCbsrilu02_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCbsrilu02_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, cuComplex *, const int *, const int *, int, bsrilu02Info_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCbsrilu02_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseCbsrilu02_bufferSizeExt:%p\n", wrapper_cusparseCbsrilu02_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCbsrilu02_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCbsrilu02_bufferSizeExt(handle, dirA, mb, nnzb, descrA, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, blockSize, info, pBufferSize);
		return retval;
	}
}