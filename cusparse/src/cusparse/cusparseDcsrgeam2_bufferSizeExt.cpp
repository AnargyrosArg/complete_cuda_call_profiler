#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDcsrgeam2_bufferSizeExt)(cusparseHandle_t, int, int, const double *, const cusparseMatDescr_t, int, const double *, const int *, const int *, const double *, const cusparseMatDescr_t, int, const double *, const int *, const int *, const cusparseMatDescr_t, const double *, const int *, const int *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDcsrgeam2_bufferSizeExt(cusparseHandle_t handle, int m, int n, const double *alpha, const cusparseMatDescr_t descrA, int nnzA, const double *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const double *beta, const cusparseMatDescr_t descrB, int nnzB, const double *csrSortedValB, const int *csrSortedRowPtrB, const int *csrSortedColIndB, const cusparseMatDescr_t descrC, const double *csrSortedValC, const int *csrSortedRowPtrC, const int *csrSortedColIndC, size_t *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDcsrgeam2_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDcsrgeam2_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const double *, const cusparseMatDescr_t, int, const double *, const int *, const int *, const double *, const cusparseMatDescr_t, int, const double *, const int *, const int *, const cusparseMatDescr_t, const double *, const int *, const int *, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDcsrgeam2_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseDcsrgeam2_bufferSizeExt:%p\n", wrapper_cusparseDcsrgeam2_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDcsrgeam2_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDcsrgeam2_bufferSizeExt(handle, m, n, alpha, descrA, nnzA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, beta, descrB, nnzB, csrSortedValB, csrSortedRowPtrB, csrSortedColIndB, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, pBufferSizeInBytes);
		return retval;
	}
}