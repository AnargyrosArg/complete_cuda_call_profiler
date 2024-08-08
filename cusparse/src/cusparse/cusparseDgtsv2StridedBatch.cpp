#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgtsv2StridedBatch)(cusparseHandle_t, int, const double *, const double *, const double *, double *, int, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgtsv2StridedBatch(cusparseHandle_t handle, int m, const double *dl, const double *d, const double *du, double *x, int batchCount, int batchStride, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgtsv2StridedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgtsv2StridedBatch = (cusparseStatus_t (*)(cusparseHandle_t, int, const double *, const double *, const double *, double *, int, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgtsv2StridedBatch");
			fprintf(stderr, "wrapper_cusparseDgtsv2StridedBatch:%p\n", wrapper_cusparseDgtsv2StridedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgtsv2StridedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgtsv2StridedBatch(handle, m, dl, d, du, x, batchCount, batchStride, pBuffer);
		return retval;
	}
}