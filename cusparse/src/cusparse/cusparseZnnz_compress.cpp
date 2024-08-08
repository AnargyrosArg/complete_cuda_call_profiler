#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZnnz_compress)(cusparseHandle_t, int, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, int *, int *, cuDoubleComplex);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZnnz_compress(cusparseHandle_t handle, int m, const cusparseMatDescr_t descr, const cuDoubleComplex *csrSortedValA, const int *csrSortedRowPtrA, int *nnzPerRow, int *nnzC, cuDoubleComplex tol) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZnnz_compress)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZnnz_compress = (cusparseStatus_t (*)(cusparseHandle_t, int, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, int *, int *, cuDoubleComplex)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZnnz_compress");
			fprintf(stderr, "wrapper_cusparseZnnz_compress:%p\n", wrapper_cusparseZnnz_compress);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZnnz_compress():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZnnz_compress(handle, m, descr, csrSortedValA, csrSortedRowPtrA, nnzPerRow, nnzC, tol);
		return retval;
	}
}