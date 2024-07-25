#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDpruneDense2csrNnzByPercentage)(cusparseHandle_t, int, int, const double *, int, float, const cusparseMatDescr_t, int *, int *, pruneInfo_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDpruneDense2csrNnzByPercentage(cusparseHandle_t handle, int m, int n, const double *A, int lda, float percentage, const cusparseMatDescr_t descrC, int *csrRowPtrC, int *nnzTotalDevHostPtr, pruneInfo_t info, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDpruneDense2csrNnzByPercentage)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDpruneDense2csrNnzByPercentage = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const double *, int, float, const cusparseMatDescr_t, int *, int *, pruneInfo_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDpruneDense2csrNnzByPercentage");
			fprintf(stderr, "wrapper_cusparseDpruneDense2csrNnzByPercentage:%p\n", wrapper_cusparseDpruneDense2csrNnzByPercentage);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDpruneDense2csrNnzByPercentage():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDpruneDense2csrNnzByPercentage(handle, m, n, A, lda, percentage, descrC, csrRowPtrC, nnzTotalDevHostPtr, info, pBuffer);
		return retval;
	}
}