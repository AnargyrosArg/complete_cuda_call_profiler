#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSbsr2csr)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, int, const cusparseMatDescr_t, float *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSbsr2csr(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nb, const cusparseMatDescr_t descrA, const float *bsrSortedValA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int blockDim, const cusparseMatDescr_t descrC, float *csrSortedValC, int *csrSortedRowPtrC, int *csrSortedColIndC) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSbsr2csr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSbsr2csr = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const float *, const int *, const int *, int, const cusparseMatDescr_t, float *, int *, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSbsr2csr");
			fprintf(stderr, "wrapper_cusparseSbsr2csr:%p\n", wrapper_cusparseSbsr2csr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSbsr2csr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSbsr2csr(handle, dirA, mb, nb, descrA, bsrSortedValA, bsrSortedRowPtrA, bsrSortedColIndA, blockDim, descrC, csrSortedValC, csrSortedRowPtrC, csrSortedColIndC);
		return retval;
	}
}