#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsrgeam2Nnz)(cusparseHandle_t, int, int, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsrgeam2Nnz(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, int nnzA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cusparseMatDescr_t descrB, int nnzB, const int *csrSortedRowPtrB, const int *csrSortedColIndB, const cusparseMatDescr_t descrC, int *csrSortedRowPtrC, int *nnzTotalDevHostPtr, void *workspace) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsrgeam2Nnz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsrgeam2Nnz = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int, const int *, const int *, const cusparseMatDescr_t, int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsrgeam2Nnz");
			fprintf(stderr, "wrapper_cusparseXcsrgeam2Nnz:%p\n", wrapper_cusparseXcsrgeam2Nnz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsrgeam2Nnz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsrgeam2Nnz(handle, m, n, descrA, nnzA, csrSortedRowPtrA, csrSortedColIndA, descrB, nnzB, csrSortedRowPtrB, csrSortedColIndB, descrC, csrSortedRowPtrC, nnzTotalDevHostPtr, workspace);
		return retval;
	}
}