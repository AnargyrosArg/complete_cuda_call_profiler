#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsr2gebsr)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, const cusparseMatDescr_t, cuComplex *, int *, int *, int, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsr2gebsr(cusparseHandle_t handle, cusparseDirection_t dirA, int m, int n, const cusparseMatDescr_t descrA, const cuComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cusparseMatDescr_t descrC, cuComplex *bsrSortedValC, int *bsrSortedRowPtrC, int *bsrSortedColIndC, int rowBlockDim, int colBlockDim, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsr2gebsr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsr2gebsr = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, const cusparseMatDescr_t, cuComplex *, int *, int *, int, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsr2gebsr");
			fprintf(stderr, "wrapper_cusparseCcsr2gebsr:%p\n", wrapper_cusparseCcsr2gebsr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsr2gebsr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsr2gebsr(handle, dirA, m, n, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, descrC, bsrSortedValC, bsrSortedRowPtrC, bsrSortedColIndC, rowBlockDim, colBlockDim, pBuffer);
		return retval;
	}
}