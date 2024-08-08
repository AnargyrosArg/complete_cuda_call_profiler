#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsr2dense)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, float *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsr2dense(cusparseHandle_t handle, int m, int n, const cusparseMatDescr_t descrA, const float *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, float *A, int lda) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsr2dense)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsr2dense = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, float *, int)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsr2dense");
			fprintf(stderr, "wrapper_cusparseScsr2dense:%p\n", wrapper_cusparseScsr2dense);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsr2dense():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsr2dense(handle, m, n, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, A, lda);
		return retval;
	}
}