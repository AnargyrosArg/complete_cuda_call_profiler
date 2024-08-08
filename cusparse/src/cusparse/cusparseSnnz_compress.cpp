#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSnnz_compress)(cusparseHandle_t, int, const cusparseMatDescr_t, const float *, const int *, int *, int *, float);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSnnz_compress(cusparseHandle_t handle, int m, const cusparseMatDescr_t descr, const float *csrSortedValA, const int *csrSortedRowPtrA, int *nnzPerRow, int *nnzC, float tol) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSnnz_compress)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSnnz_compress = (cusparseStatus_t (*)(cusparseHandle_t, int, const cusparseMatDescr_t, const float *, const int *, int *, int *, float)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSnnz_compress");
			fprintf(stderr, "wrapper_cusparseSnnz_compress:%p\n", wrapper_cusparseSnnz_compress);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSnnz_compress():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSnnz_compress(handle, m, descr, csrSortedValA, csrSortedRowPtrA, nnzPerRow, nnzC, tol);
		return retval;
	}
}