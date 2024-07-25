#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpruneCsr2csrNnz)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, const float *, const cusparseMatDescr_t, int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpruneCsr2csrNnz(cusparseHandle_t handle, int m, int n, int nnzA, const cusparseMatDescr_t descrA, const float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const float *threshold, const cusparseMatDescr_t descrC, int *csrSortedRowPtrC, int *nnzTotalDevHostPtr, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpruneCsr2csrNnz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpruneCsr2csrNnz = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, const float *, const cusparseMatDescr_t, int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpruneCsr2csrNnz");
			fprintf(stderr, "wrapper_cusparseSpruneCsr2csrNnz:%p\n", wrapper_cusparseSpruneCsr2csrNnz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpruneCsr2csrNnz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpruneCsr2csrNnz(handle, m, n, nnzA, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, threshold, descrC, csrSortedRowPtrC, nnzTotalDevHostPtr, pBuffer);
		return retval;
	}
}