#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDbsrxmv)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, int, int, const double *, const cusparseMatDescr_t, const double *, const int *, const int *, const int *, const int *, int, const double *, const double *, double *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDbsrxmv(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, int sizeOfMask, int mb, int nb, int nnzb, const double *alpha, const cusparseMatDescr_t descrA, const double *bsrSortedValA, const int *bsrSortedMaskPtrA, const int *bsrSortedRowPtrA, const int *bsrSortedEndPtrA, const int *bsrSortedColIndA, int blockDim, const double *x, const double *beta, double *y) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDbsrxmv)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDbsrxmv = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, int, int, const double *, const cusparseMatDescr_t, const double *, const int *, const int *, const int *, const int *, int, const double *, const double *, double *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDbsrxmv");
			fprintf(stderr, "wrapper_cusparseDbsrxmv:%p\n", wrapper_cusparseDbsrxmv);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDbsrxmv():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDbsrxmv(handle, dirA, transA, sizeOfMask, mb, nb, nnzb, alpha, descrA, bsrSortedValA, bsrSortedMaskPtrA, bsrSortedRowPtrA, bsrSortedEndPtrA, bsrSortedColIndA, blockDim, x, beta, y);
		return retval;
	}
}