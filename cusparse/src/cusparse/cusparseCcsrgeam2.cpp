#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsrgeam2)(cusparseHandle_t, int, int, const cuComplex *, const cusparseMatDescr_t, int, const cuComplex *, const int *, const int *, const cuComplex *, const cusparseMatDescr_t, int, const cuComplex *, const int *, const int *, const cusparseMatDescr_t, cuComplex *, int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsrgeam2(cusparseHandle_t handle, int m, int n, const cuComplex *alpha, const cusparseMatDescr_t descrA, int nnzA, const cuComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const cuComplex *beta, const cusparseMatDescr_t descrB, int nnzB, const cuComplex *csrSortedValB, const int *csrSortedRowPtrB, const int *csrSortedColIndB, const cusparseMatDescr_t descrC, cuComplex *csrSortedValC, int *csrSortedRowPtrC, int *csrSortedColIndC, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsrgeam2)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsrgeam2 = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cuComplex *, const cusparseMatDescr_t, int, const cuComplex *, const int *, const int *, const cuComplex *, const cusparseMatDescr_t, int, const cuComplex *, const int *, const int *, const cusparseMatDescr_t, cuComplex *, int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsrgeam2");
			fprintf(stderr, "wrapper_cusparseCcsrgeam2:%p\n", wrapper_cusparseCcsrgeam2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsrgeam2():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsrgeam2(handle, m, n, alpha, descrA, nnzA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, beta, descrB, nnzB, csrSortedValB, csrSortedRowPtrB, csrSortedColIndB, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, pBuffer);
		return retval;
	}
}