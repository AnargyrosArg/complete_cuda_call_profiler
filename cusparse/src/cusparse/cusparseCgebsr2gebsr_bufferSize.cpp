#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgebsr2gebsr_bufferSize)(cusparseHandle_t, cusparseDirection_t, int, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, int, int, int, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgebsr2gebsr_bufferSize(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nb, int nnzb, const cusparseMatDescr_t descrA, const cuComplex *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int rowBlockDimA, int colBlockDimA, int rowBlockDimC, int colBlockDimC, int *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgebsr2gebsr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgebsr2gebsr_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, int, int, int, int, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgebsr2gebsr_bufferSize");
			fprintf(stderr, "wrapper_cusparseCgebsr2gebsr_bufferSize:%p\n", wrapper_cusparseCgebsr2gebsr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgebsr2gebsr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgebsr2gebsr_bufferSize(handle, dirA, mb, nb, nnzb, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, rowBlockDimA, colBlockDimA, rowBlockDimC, colBlockDimC, pBufferSizeInBytes);
		return retval;
	}
}