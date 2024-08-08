#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsr2gebsr_bufferSize)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, int, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsr2gebsr_bufferSize(cusparseHandle_t handle, cusparseDirection_t dirA, int m, int n, const cusparseMatDescr_t descrA, const cuComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, int rowBlockDim, int colBlockDim, int *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsr2gebsr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsr2gebsr_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, int, int, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsr2gebsr_bufferSize");
			fprintf(stderr, "wrapper_cusparseCcsr2gebsr_bufferSize:%p\n", wrapper_cusparseCcsr2gebsr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsr2gebsr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsr2gebsr_bufferSize(handle, dirA, m, n, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, rowBlockDim, colBlockDim, pBufferSizeInBytes);
		return retval;
	}
}