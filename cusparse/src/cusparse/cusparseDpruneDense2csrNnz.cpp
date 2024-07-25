#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDpruneDense2csrNnz)(cusparseHandle_t, int, int, const double *, int, const double *, const cusparseMatDescr_t, int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDpruneDense2csrNnz(cusparseHandle_t handle, int m, int n, const double *A, int lda, const double *threshold, const cusparseMatDescr_t descrC, int *csrSortedRowPtrC, int *nnzTotalDevHostPtr, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDpruneDense2csrNnz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDpruneDense2csrNnz = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const double *, int, const double *, const cusparseMatDescr_t, int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDpruneDense2csrNnz");
			fprintf(stderr, "wrapper_cusparseDpruneDense2csrNnz:%p\n", wrapper_cusparseDpruneDense2csrNnz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDpruneDense2csrNnz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDpruneDense2csrNnz(handle, m, n, A, lda, threshold, descrC, csrSortedRowPtrC, nnzTotalDevHostPtr, pBuffer);
		return retval;
	}
}