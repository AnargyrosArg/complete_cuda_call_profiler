#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsr2csr_compress)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, int, const int *, cuComplex *, int *, int *, cuComplex);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsr2csr_compress(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuComplex *csrSortedValA, const int *csrSortedColIndA, const int *csrSortedRowPtrA, int nnzA, const int *nnzPerRow, cuComplex *csrSortedValC, int *csrSortedColIndC, int *csrSortedRowPtrC, cuComplex tol) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsr2csr_compress)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsr2csr_compress = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, int, const int *, cuComplex *, int *, int *, cuComplex)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsr2csr_compress");
			fprintf(stderr, "wrapper_cusparseCcsr2csr_compress:%p\n", wrapper_cusparseCcsr2csr_compress);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsr2csr_compress():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsr2csr_compress(handle, m, n, descrA, csrSortedValA, csrSortedColIndA, csrSortedRowPtrA, nnzA, nnzPerRow, csrSortedValC, csrSortedColIndC, csrSortedRowPtrC, tol);
		return retval;
	}
}