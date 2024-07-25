#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZdense2csr)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuDoubleComplex *, int, const int *, cuDoubleComplex *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZdense2csr(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuDoubleComplex *A, int lda, const int *nnzPerRow, cuDoubleComplex *csrSortedValA, int *csrSortedRowPtrA, int *csrSortedColIndA) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZdense2csr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZdense2csr = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuDoubleComplex *, int, const int *, cuDoubleComplex *, int *, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZdense2csr");
			fprintf(stderr, "wrapper_cusparseZdense2csr:%p\n", wrapper_cusparseZdense2csr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZdense2csr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZdense2csr(handle, m, n, descrA, A, lda, nnzPerRow, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA);
		return retval;
	}
}