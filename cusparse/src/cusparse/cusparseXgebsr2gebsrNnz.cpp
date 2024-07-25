#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXgebsr2gebsrNnz)(cusparseHandle_t, cusparseDirection_t, int, int, int, const cusparseMatDescr_t, const int *, const int *, int, int, const cusparseMatDescr_t, int *, int, int, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXgebsr2gebsrNnz(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nb, int nnzb, const cusparseMatDescr_t descrA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int rowBlockDimA, int colBlockDimA, const cusparseMatDescr_t descrC, int *bsrSortedRowPtrC, int rowBlockDimC, int colBlockDimC, int *nnzTotalDevHostPtr, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXgebsr2gebsrNnz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXgebsr2gebsrNnz = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, int, const cusparseMatDescr_t, const int *, const int *, int, int, const cusparseMatDescr_t, int *, int, int, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXgebsr2gebsrNnz");
			fprintf(stderr, "wrapper_cusparseXgebsr2gebsrNnz:%p\n", wrapper_cusparseXgebsr2gebsrNnz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXgebsr2gebsrNnz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXgebsr2gebsrNnz(handle, dirA, mb, nb, nnzb, descrA, bsrSortedRowPtrA, bsrSortedColIndA, rowBlockDimA, colBlockDimA, descrC, bsrSortedRowPtrC, rowBlockDimC, colBlockDimC, nnzTotalDevHostPtr, pBuffer);
		return retval;
	}
}