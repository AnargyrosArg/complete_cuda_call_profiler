#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsrsv2_bufferSizeExt)(cusparseHandle_t, cusparseOperation_t, int, int, const cusparseMatDescr_t, cuComplex *, const int *, const int *, csrsv2Info_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsrsv2_bufferSizeExt(cusparseHandle_t handle, cusparseOperation_t transA, int m, int nnz, const cusparseMatDescr_t descrA, cuComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, csrsv2Info_t info, size_t *pBufferSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsrsv2_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsrsv2_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, cusparseOperation_t, int, int, const cusparseMatDescr_t, cuComplex *, const int *, const int *, csrsv2Info_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsrsv2_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseCcsrsv2_bufferSizeExt:%p\n", wrapper_cusparseCcsrsv2_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsrsv2_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsrsv2_bufferSizeExt(handle, transA, m, nnz, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, info, pBufferSize);
		return retval;
	}
}