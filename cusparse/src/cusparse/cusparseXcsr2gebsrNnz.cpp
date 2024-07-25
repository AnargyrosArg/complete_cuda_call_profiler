#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsr2gebsrNnz)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const int *, const int *, const cusparseMatDescr_t, int *, int, int, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsr2gebsrNnz(cusparseHandle_t handle, cusparseDirection_t dirA, int m, int n, const cusparseMatDescr_t descrA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cusparseMatDescr_t descrC, int *bsrSortedRowPtrC, int rowBlockDim, int colBlockDim, int *nnzTotalDevHostPtr, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsr2gebsrNnz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsr2gebsrNnz = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const int *, const int *, const cusparseMatDescr_t, int *, int, int, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsr2gebsrNnz");
			fprintf(stderr, "wrapper_cusparseXcsr2gebsrNnz:%p\n", wrapper_cusparseXcsr2gebsrNnz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsr2gebsrNnz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsr2gebsrNnz(handle, dirA, m, n, descrA, csrSortedRowPtrA, csrSortedColIndA, descrC, bsrSortedRowPtrC, rowBlockDim, colBlockDim, nnzTotalDevHostPtr, pBuffer);
		return retval;
	}
}