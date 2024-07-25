#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsrgemm2)(cusparseHandle_t, int, int, int, const float *, const cusparseMatDescr_t, int, const float *, const int *, const int *, const cusparseMatDescr_t, int, const float *, const int *, const int *, const float *, const cusparseMatDescr_t, int, const float *, const int *, const int *, const cusparseMatDescr_t, float *, const int *, int *, const csrgemm2Info_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsrgemm2(cusparseHandle_t handle, int m, int n, int k, const float *alpha, const cusparseMatDescr_t descrA, int nnzA, const float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cusparseMatDescr_t descrB, int nnzB, const float *csrSortedValB, const int *csrSortedRowPtrB, const int *csrSortedColIndB, const float *beta, const cusparseMatDescr_t descrD, int nnzD, const float *csrSortedValD, const int *csrSortedRowPtrD, const int *csrSortedColIndD, const cusparseMatDescr_t descrC, float *csrSortedValC, const int *csrSortedRowPtrC, int *csrSortedColIndC, const csrgemm2Info_t info, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsrgemm2)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsrgemm2 = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const float *, const cusparseMatDescr_t, int, const float *, const int *, const int *, const cusparseMatDescr_t, int, const float *, const int *, const int *, const float *, const cusparseMatDescr_t, int, const float *, const int *, const int *, const cusparseMatDescr_t, float *, const int *, int *, const csrgemm2Info_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsrgemm2");
			fprintf(stderr, "wrapper_cusparseScsrgemm2:%p\n", wrapper_cusparseScsrgemm2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsrgemm2():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsrgemm2(handle, m, n, k, alpha, descrA, nnzA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, descrB, nnzB, csrSortedValB, csrSortedRowPtrB, csrSortedColIndB, beta, descrD, nnzD, csrSortedValD, csrSortedRowPtrD, csrSortedColIndD, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, info, pBuffer);
		return retval;
	}
}