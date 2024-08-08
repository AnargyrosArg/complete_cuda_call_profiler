#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgpsvInterleavedBatch)(cusparseHandle_t, int, int, float *, float *, float *, float *, float *, float *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgpsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, float *ds, float *dl, float *d, float *du, float *dw, float *x, int batchCount, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgpsvInterleavedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgpsvInterleavedBatch = (cusparseStatus_t (*)(cusparseHandle_t, int, int, float *, float *, float *, float *, float *, float *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgpsvInterleavedBatch");
			fprintf(stderr, "wrapper_cusparseSgpsvInterleavedBatch:%p\n", wrapper_cusparseSgpsvInterleavedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgpsvInterleavedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgpsvInterleavedBatch(handle, algo, m, ds, dl, d, du, dw, x, batchCount, pBuffer);
		return retval;
	}
}