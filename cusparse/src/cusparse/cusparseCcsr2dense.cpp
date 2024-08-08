#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsr2dense)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, cuComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsr2dense(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, cuComplex *A, int lda) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsr2dense)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsr2dense = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuComplex *, const int *, const int *, cuComplex *, int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsr2dense");
			fprintf(stderr, "wrapper_cusparseCcsr2dense:%p\n", wrapper_cusparseCcsr2dense);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsr2dense():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsr2dense(handle, m, n, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, A, lda);
		return retval;
	}
}