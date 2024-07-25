#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgpsvInterleavedBatch_bufferSizeExt)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgpsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle, int algo, int m, const cuDoubleComplex *ds, const cuDoubleComplex *dl, const cuDoubleComplex *d, const cuDoubleComplex *du, const cuDoubleComplex *dw, const cuDoubleComplex *x, int batchCount, size_t *pBufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgpsvInterleavedBatch_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgpsvInterleavedBatch_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgpsvInterleavedBatch_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseZgpsvInterleavedBatch_bufferSizeExt:%p\n", wrapper_cusparseZgpsvInterleavedBatch_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgpsvInterleavedBatch_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgpsvInterleavedBatch_bufferSizeExt(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBufferSizeInBytes);
		return retval;
	}
}