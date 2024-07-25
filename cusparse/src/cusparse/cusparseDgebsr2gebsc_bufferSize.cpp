#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgebsr2gebsc_bufferSize)(cusparseHandle_t, int, int, int, const double *, const int *, const int *, int, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgebsr2gebsc_bufferSize(cusparseHandle_t handle, int mb, int nb, int nnzb, const double *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int rowBlockDim, int colBlockDim, int *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgebsr2gebsc_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgebsr2gebsc_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const double *, const int *, const int *, int, int, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgebsr2gebsc_bufferSize");
			fprintf(stderr, "wrapper_cusparseDgebsr2gebsc_bufferSize:%p\n", wrapper_cusparseDgebsr2gebsc_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgebsr2gebsc_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgebsr2gebsc_bufferSize(handle, mb, nb, nnzb, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, rowBlockDim, colBlockDim, pBufferSizeInBytes);
		return retval;
	}
}