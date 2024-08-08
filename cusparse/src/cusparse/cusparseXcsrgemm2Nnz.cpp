#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsrgemm2Nnz)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int *, int *, const csrgemm2Info_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsrgemm2Nnz(cusparseHandle_t handle, int m, int n, int k, const cusparseMatDescr_t descrA, int nnzA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cusparseMatDescr_t descrB, int nnzB, const int *csrSortedRowPtrB, const int *csrSortedColIndB, const cusparseMatDescr_t descrD, int nnzD, const int *csrSortedRowPtrD, const int *csrSortedColIndD, const cusparseMatDescr_t descrC, int *csrSortedRowPtrC, int *nnzTotalDevHostPtr, const csrgemm2Info_t info, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsrgemm2Nnz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsrgemm2Nnz = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int *, int *, const csrgemm2Info_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsrgemm2Nnz");
			fprintf(stderr, "wrapper_cusparseXcsrgemm2Nnz:%p\n", wrapper_cusparseXcsrgemm2Nnz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsrgemm2Nnz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsrgemm2Nnz(handle, m, n, k, descrA, nnzA, csrSortedRowPtrA, csrSortedColIndA, descrB, nnzB, csrSortedRowPtrB, csrSortedColIndB, descrD, nnzD, csrSortedRowPtrD, csrSortedColIndD, descrC, csrSortedRowPtrC, nnzTotalDevHostPtr, info, pBuffer);
		return retval;
	}
}