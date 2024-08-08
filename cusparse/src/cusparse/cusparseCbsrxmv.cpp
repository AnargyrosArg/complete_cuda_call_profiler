#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCbsrxmv)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, int, int, const cuComplex *, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, const int *, const int *, int, const cuComplex *, const cuComplex *, cuComplex *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCbsrxmv(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, int sizeOfMask, int mb, int nb, int nnzb, const cuComplex *alpha, const cusparseMatDescr_t descrA, const cuComplex *bsrSortedValA, const int *bsrSortedMaskPtrA, const int *bsrSortedRowPtrA, const int *bsrSortedEndPtrA, const int *bsrSortedColIndA, int blockDim, const cuComplex *x, const cuComplex *beta, cuComplex *y) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCbsrxmv)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCbsrxmv = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, int, int, const cuComplex *, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, const int *, const int *, int, const cuComplex *, const cuComplex *, cuComplex *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCbsrxmv");
			fprintf(stderr, "wrapper_cusparseCbsrxmv:%p\n", wrapper_cusparseCbsrxmv);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCbsrxmv():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCbsrxmv(handle, dirA, transA, sizeOfMask, mb, nb, nnzb, alpha, descrA, bsrSortedValA, bsrSortedMaskPtrA, bsrSortedRowPtrA, bsrSortedEndPtrA, bsrSortedColIndA, blockDim, x, beta, y);
		return retval;
	}
}