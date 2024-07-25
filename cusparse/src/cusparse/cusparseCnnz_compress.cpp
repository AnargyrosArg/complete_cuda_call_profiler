#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCnnz_compress)(cusparseHandle_t, int, const cusparseMatDescr_t, const cuComplex *, const int *, int *, int *, cuComplex);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCnnz_compress(cusparseHandle_t handle, int m, const cusparseMatDescr_t descr, const cuComplex *csrSortedValA, const int *csrSortedRowPtrA, int *nnzPerRow, int *nnzC, cuComplex tol) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCnnz_compress)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCnnz_compress = (cusparseStatus_t (*)(cusparseHandle_t, int, const cusparseMatDescr_t, const cuComplex *, const int *, int *, int *, cuComplex)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCnnz_compress");
			fprintf(stderr, "wrapper_cusparseCnnz_compress:%p\n", wrapper_cusparseCnnz_compress);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCnnz_compress():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCnnz_compress(handle, m, descr, csrSortedValA, csrSortedRowPtrA, nnzPerRow, nnzC, tol);
		return retval;
	}
}