#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpruneCsr2csrByPercentage_bufferSizeExt)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, float, const cusparseMatDescr_t, const float *, const int *, const int *, pruneInfo_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpruneCsr2csrByPercentage_bufferSizeExt(cusparseHandle_t handle, int m, int n, int nnzA, const cusparseMatDescr_t descrA, const float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, float percentage, const cusparseMatDescr_t descrC, const float *csrSortedValC, const int *csrSortedRowPtrC, const int *csrSortedColIndC, pruneInfo_t info, size_t *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpruneCsr2csrByPercentage_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpruneCsr2csrByPercentage_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, float, const cusparseMatDescr_t, const float *, const int *, const int *, pruneInfo_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpruneCsr2csrByPercentage_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseSpruneCsr2csrByPercentage_bufferSizeExt:%p\n", wrapper_cusparseSpruneCsr2csrByPercentage_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpruneCsr2csrByPercentage_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpruneCsr2csrByPercentage_bufferSizeExt(handle, m, n, nnzA, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, percentage, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, info, pBufferSizeInBytes);
		return retval;
	}
}