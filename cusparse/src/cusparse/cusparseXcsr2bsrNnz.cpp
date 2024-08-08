#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsr2bsrNnz)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const int *, const int *, int, const cusparseMatDescr_t, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsr2bsrNnz(cusparseHandle_t handle, cusparseDirection_t dirA, int m, int n, const cusparseMatDescr_t descrA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, int blockDim, const cusparseMatDescr_t descrC, int *bsrSortedRowPtrC, int *nnzTotalDevHostPtr) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsr2bsrNnz)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsr2bsrNnz = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const int *, const int *, int, const cusparseMatDescr_t, int *, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsr2bsrNnz");
			fprintf(stderr, "wrapper_cusparseXcsr2bsrNnz:%p\n", wrapper_cusparseXcsr2bsrNnz);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsr2bsrNnz():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsr2bsrNnz(handle, dirA, m, n, descrA, csrSortedRowPtrA, csrSortedColIndA, blockDim, descrC, bsrSortedRowPtrC, nnzTotalDevHostPtr);
		return retval;
	}
}