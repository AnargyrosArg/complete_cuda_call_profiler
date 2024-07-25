#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpruneDense2csrNnz)(cusparseHandle_t, int, int, const float *, int, const float *, const cusparseMatDescr_t, int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpruneDense2csrNnz(cusparseHandle_t handle, int m, int n, const float *A, int lda, const float *threshold, const cusparseMatDescr_t descrC, int *csrRowPtrC, int *nnzTotalDevHostPtr, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpruneDense2csrNnz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpruneDense2csrNnz = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const float *, int, const float *, const cusparseMatDescr_t, int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpruneDense2csrNnz");
			fprintf(stderr, "wrapper_cusparseSpruneDense2csrNnz:%p\n", wrapper_cusparseSpruneDense2csrNnz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpruneDense2csrNnz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpruneDense2csrNnz(handle, m, n, A, lda, threshold, descrC, csrRowPtrC, nnzTotalDevHostPtr, pBuffer);
		return retval;
	}
}