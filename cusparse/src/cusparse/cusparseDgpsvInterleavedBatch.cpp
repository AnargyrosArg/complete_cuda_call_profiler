#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDgpsvInterleavedBatch)(cusparseHandle_t, int, int, double *, double *, double *, double *, double *, double *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDgpsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, double *ds, double *dl, double *d, double *du, double *dw, double *x, int batchCount, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDgpsvInterleavedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDgpsvInterleavedBatch = (cusparseStatus_t (*)(cusparseHandle_t, int, int, double *, double *, double *, double *, double *, double *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDgpsvInterleavedBatch");
			fprintf(stderr, "wrapper_cusparseDgpsvInterleavedBatch:%p\n", wrapper_cusparseDgpsvInterleavedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDgpsvInterleavedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDgpsvInterleavedBatch(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBuffer);
		return retval;
	}
}