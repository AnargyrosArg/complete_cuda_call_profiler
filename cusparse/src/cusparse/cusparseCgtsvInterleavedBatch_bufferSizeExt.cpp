#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCgtsvInterleavedBatch_bufferSizeExt)(cusparseHandle_t, int, int, const cuComplex *, const cuComplex *, const cuComplex *, const cuComplex *, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCgtsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle, int algo, int m, const cuComplex *dl, const cuComplex *d, const cuComplex *du, const cuComplex *x, int batchCount, size_t *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCgtsvInterleavedBatch_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCgtsvInterleavedBatch_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cuComplex *, const cuComplex *, const cuComplex *, const cuComplex *, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCgtsvInterleavedBatch_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseCgtsvInterleavedBatch_bufferSizeExt:%p\n", wrapper_cusparseCgtsvInterleavedBatch_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCgtsvInterleavedBatch_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCgtsvInterleavedBatch_bufferSizeExt(handle, algo, m, dl, d, du, x, batchCount, pBufferSizeInBytes);
		return retval;
	}
}