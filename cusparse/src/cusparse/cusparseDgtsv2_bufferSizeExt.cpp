#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgtsv2_bufferSizeExt)(cusparseHandle_t, int, int, const double *, const double *, const double *, const double *, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgtsv2_bufferSizeExt(cusparseHandle_t handle, int m, int n, const double *dl, const double *d, const double *du, const double *B, int ldb, size_t *bufferSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgtsv2_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgtsv2_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const double *, const double *, const double *, const double *, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgtsv2_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseDgtsv2_bufferSizeExt:%p\n", wrapper_cusparseDgtsv2_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgtsv2_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgtsv2_bufferSizeExt(handle, m, n, dl, d, du, B, ldb, bufferSizeInBytes);
		return retval;
	}
}