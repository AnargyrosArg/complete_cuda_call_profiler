#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDnnz_compress)(cusparseHandle_t, int, const cusparseMatDescr_t, const double *, const int *, int *, int *, double);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDnnz_compress(cusparseHandle_t handle, int m, const cusparseMatDescr_t descr, const double *csrSortedValA, const int *csrSortedRowPtrA, int *nnzPerRow, int *nnzC, double tol) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDnnz_compress)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDnnz_compress = (cusparseStatus_t (*)(cusparseHandle_t, int, const cusparseMatDescr_t, const double *, const int *, int *, int *, double)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDnnz_compress");
			fprintf(stderr, "wrapper_cusparseDnnz_compress:%p\n", wrapper_cusparseDnnz_compress);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDnnz_compress():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDnnz_compress(handle, m, descr, csrSortedValA, csrSortedRowPtrA, nnzPerRow, nnzC, tol);
		return retval;
	}
}