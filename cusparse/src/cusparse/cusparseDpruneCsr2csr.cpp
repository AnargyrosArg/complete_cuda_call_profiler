#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDpruneCsr2csr)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, const double *, const cusparseMatDescr_t, double *, const int *, int *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDpruneCsr2csr(cusparseHandle_t handle, int m, int n, int nnzA, const cusparseMatDescr_t descrA, const double *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, const double *threshold, const cusparseMatDescr_t descrC, double *csrSortedValC, const int *csrSortedRowPtrC, int *csrSortedColIndC, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDpruneCsr2csr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDpruneCsr2csr = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, const double *, const cusparseMatDescr_t, double *, const int *, int *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDpruneCsr2csr");
			fprintf(stderr, "wrapper_cusparseDpruneCsr2csr:%p\n", wrapper_cusparseDpruneCsr2csr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDpruneCsr2csr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDpruneCsr2csr(handle, m, n, nnzA, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, threshold, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC, pBuffer);
		return retval;
	}
}