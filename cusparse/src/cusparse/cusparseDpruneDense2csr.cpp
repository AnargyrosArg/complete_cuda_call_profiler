#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDpruneDense2csr)(cusparseHandle_t, int, int, const double *, int, const double *, const cusparseMatDescr_t, double *, const int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDpruneDense2csr(cusparseHandle_t handle, int m, int n, const double *A, int lda, const double *threshold, const cusparseMatDescr_t descrC, double *csrSortedValC, const int *csrSortedRowPtrC, int *csrSortedColIndC, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDpruneDense2csr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDpruneDense2csr = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const double *, int, const double *, const cusparseMatDescr_t, double *, const int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDpruneDense2csr");
			fprintf(stderr, "wrapper_cusparseDpruneDense2csr:%p\n", wrapper_cusparseDpruneDense2csr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDpruneDense2csr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDpruneDense2csr(handle, m, n, A, lda, threshold, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, pBuffer);
		return retval;
	}
}