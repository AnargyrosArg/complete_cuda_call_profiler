#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDpruneCsr2csrByPercentage)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, float, const cusparseMatDescr_t, double *, const int *, int *, pruneInfo_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDpruneCsr2csrByPercentage(cusparseHandle_t handle, int m, int n, int nnzA, const cusparseMatDescr_t descrA, const double *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, float percentage, const cusparseMatDescr_t descrC, double *csrSortedValC, const int *csrSortedRowPtrC, int *csrSortedColIndC, pruneInfo_t info, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDpruneCsr2csrByPercentage)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDpruneCsr2csrByPercentage = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, float, const cusparseMatDescr_t, double *, const int *, int *, pruneInfo_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDpruneCsr2csrByPercentage");
			fprintf(stderr, "wrapper_cusparseDpruneCsr2csrByPercentage:%p\n", wrapper_cusparseDpruneCsr2csrByPercentage);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDpruneCsr2csrByPercentage():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDpruneCsr2csrByPercentage(handle, m, n, nnzA, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, percentage, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, info, pBuffer);
		return retval;
	}
}