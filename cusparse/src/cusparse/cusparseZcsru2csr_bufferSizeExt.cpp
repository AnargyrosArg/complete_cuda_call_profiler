#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZcsru2csr_bufferSizeExt)(cusparseHandle_t, int, int, int, cuDoubleComplex *, const int *, int *, csru2csrInfo_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZcsru2csr_bufferSizeExt(cusparseHandle_t handle, int m, int n, int nnz, cuDoubleComplex *csrVal, const int *csrRowPtr, int *csrColInd, csru2csrInfo_t info, size_t *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZcsru2csr_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZcsru2csr_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, int, cuDoubleComplex *, const int *, int *, csru2csrInfo_t, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZcsru2csr_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseZcsru2csr_bufferSizeExt:%p\n", wrapper_cusparseZcsru2csr_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZcsru2csr_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZcsru2csr_bufferSizeExt(handle, m, n, nnz, csrVal, csrRowPtr, csrColInd, info, pBufferSizeInBytes);
		return retval;
	}
}