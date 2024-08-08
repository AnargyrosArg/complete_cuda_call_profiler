#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZbsrmm)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, cusparseOperation_t, int, int, int, int, const cuDoubleComplex *, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, const int, const cuDoubleComplex *, const int, const cuDoubleComplex *, cuDoubleComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZbsrmm(cusparseHandle_t handle, cusparseDirection_t dirA, cusparseOperation_t transA, cusparseOperation_t transB, int mb, int n, int kb, int nnzb, const cuDoubleComplex *alpha, const cusparseMatDescr_t descrA, const cuDoubleComplex *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, const int blockSize, const cuDoubleComplex *B, const int ldb, const cuDoubleComplex *beta, cuDoubleComplex *C, int ldc) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZbsrmm)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZbsrmm = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, cusparseOperation_t, cusparseOperation_t, int, int, int, int, const cuDoubleComplex *, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, const int, const cuDoubleComplex *, const int, const cuDoubleComplex *, cuDoubleComplex *, int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZbsrmm");
			fprintf(stderr, "wrapper_cusparseZbsrmm:%p\n", wrapper_cusparseZbsrmm);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZbsrmm():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZbsrmm(handle, dirA, transA, transB, mb, n, kb, nnzb, alpha, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, blockSize, B, ldb, beta, C, ldc);
		return retval;
	}
}