#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDdense2csc)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const double *, int, const int *, double *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDdense2csc(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const double *A, int lda, const int *nnzPerCol, double *cscSortedValA, int *cscSortedRowIndA, int *cscSortedColPtrA) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDdense2csc)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDdense2csc = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const double *, int, const int *, double *, int *, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDdense2csc");
			fprintf(stderr, "wrapper_cusparseDdense2csc:%p\n", wrapper_cusparseDdense2csc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDdense2csc():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDdense2csc(handle, m, n, descrA, A, lda, nnzPerCol, cscSortedValA, cscSortedRowIndA, cscSortedColPtrA);
		return retval;
	}
}