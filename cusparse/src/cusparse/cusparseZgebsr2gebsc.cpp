#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgebsr2gebsc)(cusparseHandle_t, int, int, int, const cuDoubleComplex *, const int *, const int *, int, int, cuDoubleComplex *, int *, int *, cusparseAction_t, cusparseIndexBase_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgebsr2gebsc(cusparseHandle_t handle, int mb, int nb, int nnzb, const cuDoubleComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int rowBlockDim, int colBlockDim, cuDoubleComplex *bscVal, int *bscRowInd, int *bscColPtr, cusparseAction_t copyValues, cusparseIndexBase_t idxBase, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgebsr2gebsc)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgebsr2gebsc = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cuDoubleComplex *, const int *, const int *, int, int, cuDoubleComplex *, int *, int *, cusparseAction_t, cusparseIndexBase_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgebsr2gebsc");
			fprintf(stderr, "wrapper_cusparseZgebsr2gebsc:%p\n", wrapper_cusparseZgebsr2gebsc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgebsr2gebsc():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgebsr2gebsc(handle, mb, nb, nnzb, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, rowBlockDim, colBlockDim, bscVal, bscRowInd, bscColPtr, copyValues, idxBase, pBuffer);
		return retval;
	}
}