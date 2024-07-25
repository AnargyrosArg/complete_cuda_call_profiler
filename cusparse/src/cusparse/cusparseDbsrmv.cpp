#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDbsrmv)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, int, const double *, const cusparseMatDescr_t, const double *, const int *, const int *, int, const double *, const double *, double *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDbsrmv(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, int mb, int nb, int nnzb, const double *alpha, const cusparseMatDescr_t descrA, const double *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int blockDim, const double *x, const double *beta, double *y) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDbsrmv)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDbsrmv = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, int, int, int, const double *, const cusparseMatDescr_t, const double *, const int *, const int *, int, const double *, const double *, double *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDbsrmv");
			fprintf(stderr, "wrapper_cusparseDbsrmv:%p\n", wrapper_cusparseDbsrmv);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDbsrmv():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDbsrmv(handle, dirA, transA, mb, nb, nnzb, alpha, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, blockDim, x, beta, y);
		return retval;
	}
}