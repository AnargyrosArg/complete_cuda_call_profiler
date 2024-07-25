#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgebsr2gebsr)(cusparseHandle_t, cusparseDirection_t, int, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, int, int, const cusparseMatDescr_t, float *, int *, int *, int, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgebsr2gebsr(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nb, int nnzb, const cusparseMatDescr_t descrA, const float *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int rowBlockDimA, int colBlockDimA, const cusparseMatDescr_t descrC, float *bsrSortedValC, int *bsrSortedRowPtrC, int *bsrSortedColIndC, int rowBlockDimC, int colBlockDimC, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgebsr2gebsr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgebsr2gebsr = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, int, int, const cusparseMatDescr_t, float *, int *, int *, int, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgebsr2gebsr");
			fprintf(stderr, "wrapper_cusparseSgebsr2gebsr:%p\n", wrapper_cusparseSgebsr2gebsr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgebsr2gebsr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgebsr2gebsr(handle, dirA, mb, nb, nnzb, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, rowBlockDimA, colBlockDimA, descrC, bsrSortedValC, bsrSortedRowPtrC, bsrSortedColIndC, rowBlockDimC, colBlockDimC, pBuffer);
		return retval;
	}
}