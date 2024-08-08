#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgtsv2StridedBatch_bufferSizeExt)(cusparseHandle_t, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, int, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgtsv2StridedBatch_bufferSizeExt(cusparseHandle_t handle, int m, const cuDoubleComplex *dl, const cuDoubleComplex *d, const cuDoubleComplex *du, const cuDoubleComplex *x, int batchCount, int batchStride, size_t *bufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgtsv2StridedBatch_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgtsv2StridedBatch_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, int, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgtsv2StridedBatch_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseZgtsv2StridedBatch_bufferSizeExt:%p\n", wrapper_cusparseZgtsv2StridedBatch_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgtsv2StridedBatch_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgtsv2StridedBatch_bufferSizeExt(handle, m, dl, d, du, x, batchCount, batchStride, bufferSizeInBytes);
		return retval;
	}
}