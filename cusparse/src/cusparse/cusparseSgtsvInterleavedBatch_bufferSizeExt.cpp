#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgtsvInterleavedBatch_bufferSizeExt)(cusparseHandle_t, int, int, const float *, const float *, const float *, const float *, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgtsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle, int algo, int m, const float *dl, const float *d, const float *du, const float *x, int batchCount, size_t *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgtsvInterleavedBatch_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgtsvInterleavedBatch_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const float *, const float *, const float *, const float *, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgtsvInterleavedBatch_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseSgtsvInterleavedBatch_bufferSizeExt:%p\n", wrapper_cusparseSgtsvInterleavedBatch_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgtsvInterleavedBatch_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgtsvInterleavedBatch_bufferSizeExt(handle, algo, m, dl, d, du, x, batchCount, pBufferSizeInBytes);
		return retval;
	}
}