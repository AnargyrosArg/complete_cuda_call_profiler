#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpruneDense2csrByPercentage)(cusparseHandle_t, int, int, const float *, int, float, const cusparseMatDescr_t, float *, const int *, int *, pruneInfo_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpruneDense2csrByPercentage(cusparseHandle_t handle, int m, int n, const float *A, int lda, float percentage, const cusparseMatDescr_t descrC, float *csrSortedValC, const int *csrSortedRowPtrC, int *csrSortedColIndC, pruneInfo_t info, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpruneDense2csrByPercentage)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpruneDense2csrByPercentage = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const float *, int, float, const cusparseMatDescr_t, float *, const int *, int *, pruneInfo_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpruneDense2csrByPercentage");
			fprintf(stderr, "wrapper_cusparseSpruneDense2csrByPercentage:%p\n", wrapper_cusparseSpruneDense2csrByPercentage);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpruneDense2csrByPercentage():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpruneDense2csrByPercentage(handle, m, n, A, lda, percentage, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, info, pBuffer);
		return retval;
	}
}