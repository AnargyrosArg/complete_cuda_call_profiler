#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsrsv2_bufferSize)(cusparseHandle_t, cusparseOperation_t, int, int, const cusparseMatDescr_t, float *, const int *, const int *, csrsv2Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsrsv2_bufferSize(cusparseHandle_t handle, cusparseOperation_t transA, int m, int nnz, const cusparseMatDescr_t descrA, float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csrsv2Info_t info, int *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsrsv2_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsrsv2_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, const cusparseMatDescr_t, float *, const int *, const int *, csrsv2Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsrsv2_bufferSize");
			fprintf(stderr, "wrapper_cusparseScsrsv2_bufferSize:%p\n", wrapper_cusparseScsrsv2_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsrsv2_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsrsv2_bufferSize(handle, transA, m, nnz, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, info, pBufferSizeInBytes);
		return retval;
	}
}