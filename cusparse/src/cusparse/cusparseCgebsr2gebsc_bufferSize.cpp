#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgebsr2gebsc_bufferSize)(cusparseHandle_t, int, int, int, const cuComplex *, const int *, const int *, int, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgebsr2gebsc_bufferSize(cusparseHandle_t handle, int mb, int nb, int nnzb, const cuComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int rowBlockDim, int colBlockDim, int *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgebsr2gebsc_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgebsr2gebsc_bufferSize = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cuComplex *, const int *, const int *, int, int, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgebsr2gebsc_bufferSize");
			fprintf(stderr, "wrapper_cusparseCgebsr2gebsc_bufferSize:%p\n", wrapper_cusparseCgebsr2gebsc_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgebsr2gebsc_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgebsr2gebsc_bufferSize(handle, mb, nb, nnzb, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, rowBlockDim, colBlockDim, pBufferSizeInBytes);
		return retval;
	}
}