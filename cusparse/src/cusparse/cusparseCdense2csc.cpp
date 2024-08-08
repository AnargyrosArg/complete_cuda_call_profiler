#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCdense2csc)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuComplex *, int, const int *, cuComplex *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCdense2csc(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const cuComplex *A, int lda, const int *nnzPerCol, cuComplex *cscSortedValA, int *cscSortedRowIndA, int *cscSortedColPtrA) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCdense2csc)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCdense2csc = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const cuComplex *, int, const int *, cuComplex *, int *, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCdense2csc");
			fprintf(stderr, "wrapper_cusparseCdense2csc:%p\n", wrapper_cusparseCdense2csc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCdense2csc():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCdense2csc(handle, m, n, descrA, A, lda, nnzPerCol, cscSortedValA, cscSortedRowIndA, cscSortedColPtrA);
		return retval;
	}
}