#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgtsv2_bufferSizeExt)(cusparseHandle_t, int, int, const float *, const float *, const float *, const float *, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgtsv2_bufferSizeExt(cusparseHandle_t handle, int m, int n, const float *dl, const float *d, const float *du, const float *B, int ldb, size_t *bufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgtsv2_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgtsv2_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const float *, const float *, const float *, const float *, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgtsv2_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseSgtsv2_bufferSizeExt:%p\n", wrapper_cusparseSgtsv2_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgtsv2_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgtsv2_bufferSizeExt(handle, m, n, dl, d, du, B, ldb, bufferSizeInBytes);
		return retval;
	}
}