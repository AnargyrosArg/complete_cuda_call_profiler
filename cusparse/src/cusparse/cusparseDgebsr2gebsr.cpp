#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgebsr2gebsr)(cusparseHandle_t, cusparseDirection_t, int, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, int, int, const cusparseMatDescr_t, double *, int *, int *, int, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgebsr2gebsr(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nb, int nnzb, const cusparseMatDescr_t descrA, const double *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int rowBlockDimA, int colBlockDimA, const cusparseMatDescr_t descrC, double *bsrSortedValC, int *bsrSortedRowPtrC, int *bsrSortedColIndC, int rowBlockDimC, int colBlockDimC, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgebsr2gebsr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgebsr2gebsr = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, int, int, const cusparseMatDescr_t, double *, int *, int *, int, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgebsr2gebsr");
			fprintf(stderr, "wrapper_cusparseDgebsr2gebsr:%p\n", wrapper_cusparseDgebsr2gebsr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgebsr2gebsr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgebsr2gebsr(handle, dirA, mb, nb, nnzb, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, rowBlockDimA, colBlockDimA, descrC, bsrSortedValC, bsrSortedRowPtrC, bsrSortedColIndC, rowBlockDimC, colBlockDimC, pBuffer);
		return retval;
	}
}