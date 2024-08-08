#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZcsc2dense)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, cuDoubleComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZcsc2dense(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuDoubleComplex *cscSortedValA, const int *cscSortedRowIndA, const int *cscSortedColPtrA, cuDoubleComplex *A, int lda) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZcsc2dense)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZcsc2dense = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, cuDoubleComplex *, int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZcsc2dense");
			fprintf(stderr, "wrapper_cusparseZcsc2dense:%p\n", wrapper_cusparseZcsc2dense);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZcsc2dense():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZcsc2dense(handle, m, n, descrA, cscSortedValA, cscSortedRowIndA, cscSortedColPtrA, A, lda);
		return retval;
	}
}