#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDpruneDense2csrByPercentage)(cusparseHandle_t, int, int, const double *, int, float, const cusparseMatDescr_t, double *, const int *, int *, pruneInfo_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDpruneDense2csrByPercentage(cusparseHandle_t handle, int m, int n, const double *A, int lda, float percentage, const cusparseMatDescr_t descrC, double *csrSortedValC, const int *csrSortedRowPtrC, int *csrSortedColIndC, pruneInfo_t info, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDpruneDense2csrByPercentage)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDpruneDense2csrByPercentage = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const double *, int, float, const cusparseMatDescr_t, double *, const int *, int *, pruneInfo_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDpruneDense2csrByPercentage");
			fprintf(stderr, "wrapper_cusparseDpruneDense2csrByPercentage:%p\n", wrapper_cusparseDpruneDense2csrByPercentage);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDpruneDense2csrByPercentage():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDpruneDense2csrByPercentage(handle, m, n, A, lda, percentage, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, info, pBuffer);
		return retval;
	}
}