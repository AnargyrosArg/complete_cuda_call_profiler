#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZcsr2bsr)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, int, const cusparseMatDescr_t, cuDoubleComplex *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZcsr2bsr(cusparseHandle_t handle, cusparseDirection_t dirA, int m, int n, const cusparseMatDescr_t descrA, const cuDoubleComplex *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, int blockDim, const cusparseMatDescr_t descrC, cuDoubleComplex *bsrSortedValC, int *bsrSortedRowPtrC, int *bsrSortedColIndC) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZcsr2bsr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZcsr2bsr = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const cuDoubleComplex *, const int *, const int *, int, const cusparseMatDescr_t, cuDoubleComplex *, int *, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZcsr2bsr");
			fprintf(stderr, "wrapper_cusparseZcsr2bsr:%p\n", wrapper_cusparseZcsr2bsr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZcsr2bsr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZcsr2bsr(handle, dirA, m, n, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, blockDim, descrC, bsrSortedValC, bsrSortedRowPtrC, bsrSortedColIndC);
		return retval;
	}
}