#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXgebsr2csr)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const int *, const int *, int, int, const cusparseMatDescr_t, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXgebsr2csr(cusparseHandle_t handle, cusparseDirection_t dirA, int mb, int nb, const cusparseMatDescr_t descrA, const int *bsrSortedRowPtrA, const int *bsrSortedColIndA, int rowBlockDim, int colBlockDim, const cusparseMatDescr_t descrC, int *csrSortedRowPtrC, int *csrSortedColIndC) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXgebsr2csr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXgebsr2csr = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const int *, const int *, int, int, const cusparseMatDescr_t, int *, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXgebsr2csr");
			fprintf(stderr, "wrapper_cusparseXgebsr2csr:%p\n", wrapper_cusparseXgebsr2csr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXgebsr2csr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXgebsr2csr(handle, dirA, mb, nb, descrA, bsrSortedRowPtrA, bsrSortedColIndA, rowBlockDim, colBlockDim, descrC, csrSortedRowPtrC, csrSortedColIndC);
		return retval;
	}
}