#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgpsvInterleavedBatch_bufferSizeExt)(cusparseHandle_t, int, int, const float *, const float *, const float *, const float *, const float *, const float *, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgpsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle, int algo, int m, const float *ds, const float *dl, const float *d, const float *du, const float *dw, const float *x, int batchCount, size_t *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgpsvInterleavedBatch_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgpsvInterleavedBatch_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const float *, const float *, const float *, const float *, const float *, const float *, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgpsvInterleavedBatch_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseSgpsvInterleavedBatch_bufferSizeExt:%p\n", wrapper_cusparseSgpsvInterleavedBatch_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgpsvInterleavedBatch_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgpsvInterleavedBatch_bufferSizeExt(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBufferSizeInBytes);
		return retval;
	}
}