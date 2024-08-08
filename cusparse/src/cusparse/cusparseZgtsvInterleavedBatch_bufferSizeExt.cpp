#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgtsvInterleavedBatch_bufferSizeExt)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgtsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle, int algo, int m, const cuDoubleComplex *dl, const cuDoubleComplex *d, const cuDoubleComplex *du, const cuDoubleComplex *x, int batchCount, size_t *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgtsvInterleavedBatch_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgtsvInterleavedBatch_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgtsvInterleavedBatch_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseZgtsvInterleavedBatch_bufferSizeExt:%p\n", wrapper_cusparseZgtsvInterleavedBatch_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgtsvInterleavedBatch_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgtsvInterleavedBatch_bufferSizeExt(handle, algo, m, dl, d, du, x, batchCount, pBufferSizeInBytes);
		return retval;
	}
}