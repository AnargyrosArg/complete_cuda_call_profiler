#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgtsv2)(cusparseHandle_t, int, int, const float *, const float *, const float *, float *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgtsv2(cusparseHandle_t handle, int m, int n, const float *dl, const float *d, const float *du, float *B, int ldb, void *pBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgtsv2)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgtsv2 = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const float *, const float *, const float *, float *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgtsv2");
			fprintf(stderr, "wrapper_cusparseSgtsv2:%p\n", wrapper_cusparseSgtsv2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgtsv2():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgtsv2(handle, m, n, dl, d, du, B, ldb, pBuffer);
		return retval;
	}
}