#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCdense2csr)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuComplex *, int, const int *, cuComplex *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCdense2csr(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuComplex *A, int lda, const int *nnzPerRow, cuComplex *csrSortedValA, int *csrSortedRowPtrA, int *csrSortedColIndA) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCdense2csr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCdense2csr = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuComplex *, int, const int *, cuComplex *, int *, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCdense2csr");
			fprintf(stderr, "wrapper_cusparseCdense2csr:%p\n", wrapper_cusparseCdense2csr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCdense2csr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCdense2csr(handle, m, n, descrA, A, lda, nnzPerRow, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA);
		return retval;
	}
}