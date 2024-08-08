#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsrgeam2)(cusparseHandle_t, int, int, const float *, const cusparseMatDescr_t, int, const float *, const int *, const int *, const float *, const cusparseMatDescr_t, int, const float *, const int *, const int *, const cusparseMatDescr_t, float *, int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsrgeam2(cusparseHandle_t handle, int m, int n, const float *alpha, const cusparseMatDescr_t descrA, int nnzA, const float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const float *beta, const cusparseMatDescr_t descrB, int nnzB, const float *csrSortedValB, const int *csrSortedRowPtrB, const int *csrSortedColIndB, const cusparseMatDescr_t descrC, float *csrSortedValC, int *csrSortedRowPtrC, int *csrSortedColIndC, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsrgeam2)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsrgeam2 = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const float *, const cusparseMatDescr_t, int, const float *, const int *, const int *, const float *, const cusparseMatDescr_t, int, const float *, const int *, const int *, const cusparseMatDescr_t, float *, int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsrgeam2");
			fprintf(stderr, "wrapper_cusparseScsrgeam2:%p\n", wrapper_cusparseScsrgeam2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsrgeam2():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsrgeam2(handle, m, n, alpha, descrA, nnzA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, beta, descrB, nnzB, csrSortedValB, csrSortedRowPtrB, csrSortedColIndB, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, pBuffer);
		return retval;
	}
}