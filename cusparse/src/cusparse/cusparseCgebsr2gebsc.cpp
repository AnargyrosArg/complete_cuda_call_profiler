#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgebsr2gebsc)(cusparseHandle_t, int, int, int, const cuComplex *, const int *, const int *, int, int, cuComplex *, int *, int *, cusparseAction_t, cusparseIndexBase_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgebsr2gebsc(cusparseHandle_t handle, int mb, int nb, int nnzb, const cuComplex *bsrSortedVal, const int *bsrSortedRowPtr, const int *bsrSortedColInd, int rowBlockDim, int colBlockDim, cuComplex *bscVal, int *bscRowInd, int *bscColPtr, cusparseAction_t copyValues, cusparseIndexBase_t idxBase, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgebsr2gebsc)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgebsr2gebsc = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, const cuComplex *, const int *, const int *, int, int, cuComplex *, int *, int *, cusparseAction_t, cusparseIndexBase_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgebsr2gebsc");
			fprintf(stderr, "wrapper_cusparseCgebsr2gebsc:%p\n", wrapper_cusparseCgebsr2gebsc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgebsr2gebsc():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgebsr2gebsc(handle, mb, nb, nnzb, bsrSortedVal, bsrSortedRowPtr, bsrSortedColInd, rowBlockDim, colBlockDim, bscVal, bscRowInd, bscColPtr, copyValues, idxBase, pBuffer);
		return retval;
	}
}