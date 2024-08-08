#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgtsvInterleavedBatch_bufferSizeExt)(cusparseHandle_t, int, int, const double *, const double *, const double *, const double *, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgtsvInterleavedBatch_bufferSizeExt(cusparseHandle_t handle, int algo, int m, const double *dl, const double *d, const double *du, const double *x, int batchCount, size_t *pBufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgtsvInterleavedBatch_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgtsvInterleavedBatch_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const double *, const double *, const double *, const double *, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgtsvInterleavedBatch_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseDgtsvInterleavedBatch_bufferSizeExt:%p\n", wrapper_cusparseDgtsvInterleavedBatch_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgtsvInterleavedBatch_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgtsvInterleavedBatch_bufferSizeExt(handle, algo, m, dl, d, du, x, batchCount, pBufferSizeInBytes);
		return retval;
	}
}