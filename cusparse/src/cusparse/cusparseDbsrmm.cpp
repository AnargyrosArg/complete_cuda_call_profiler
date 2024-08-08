#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDbsrmm)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, cusparseOperation_t, int, int, int, int, const double *, const cusparseMatDescr_t, const double *, const int *, const int *, const int, const double *, const int, const double *, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDbsrmm(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, cusparseOperation_t transB, int mb, int n, int kb, int nnzb, const double *alpha, const cusparseMatDescr_t descrA, const double *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, const int blockSize, const double *B, const int ldb, const double *beta, double *C, int ldc) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDbsrmm)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDbsrmm = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, cusparseOperation_t, int, int, int, int, const double *, const cusparseMatDescr_t, const double *, const int *, const int *, const int, const double *, const int, const double *, double *, int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDbsrmm");
			fprintf(stderr, "wrapper_cusparseDbsrmm:%p\n", wrapper_cusparseDbsrmm);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDbsrmm():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDbsrmm(handle, dirA, transA, transB, mb, n, kb, nnzb, alpha, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, blockSize, B, ldb, beta, C, ldc);
		return retval;
	}
}