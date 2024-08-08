#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsrsm2_bufferSizeExt)(cusparseHandle_t, int, cusparseOperation_t, cusparseOperation_t, int, int, int, const cuComplex *, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, const cuComplex *, int, csrsm2Info_t, cusparseSolvePolicy_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsrsm2_bufferSizeExt(cusparseHandle_t handle, int algo, cusparseOperation_t transA, cusparseOperation_t transB, int m, int nrhs, int nnz, const cuComplex *alpha, const cusparseMatDescr_t descrA, const cuComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cuComplex *B, int ldb, csrsm2Info_t info, cusparseSolvePolicy_t policy, size_t *pBufferSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsrsm2_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsrsm2_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, cusparseOperation_t, cusparseOperation_t, int, int, int, const cuComplex *, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, const cuComplex *, int, csrsm2Info_t, cusparseSolvePolicy_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsrsm2_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseCcsrsm2_bufferSizeExt:%p\n", wrapper_cusparseCcsrsm2_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsrsm2_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsrsm2_bufferSizeExt(handle, algo, transA, transB, m, nrhs, nnz, alpha, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, B, ldb, info, policy, pBufferSize);
		return retval;
	}
}