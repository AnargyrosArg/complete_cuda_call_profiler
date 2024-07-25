#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDcsr2gebsr_bufferSizeExt)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, int, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDcsr2gebsr_bufferSizeExt(cusparseHandle_t handle, cusparseDirection_t dirA, int m, int n, const cusparseMatDescr_t descrA, const double *csrSortedValA, const int *csrSortedRowPtrA, const int *csrSortedColIndA, int rowBlockDim, int colBlockDim, size_t *pBufferSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDcsr2gebsr_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDcsr2gebsr_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, cusparseDirection_t, int, int, const cusparseMatDescr_t, const double *, const int *, const int *, int, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDcsr2gebsr_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseDcsr2gebsr_bufferSizeExt:%p\n", wrapper_cusparseDcsr2gebsr_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDcsr2gebsr_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDcsr2gebsr_bufferSizeExt(handle, dirA, m, n, descrA, csrSortedValA, csrSortedRowPtrA, csrSortedColIndA, rowBlockDim, colBlockDim, pBufferSize);
		return retval;
	}
}