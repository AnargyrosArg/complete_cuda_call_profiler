#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgtsvInterleavedBatch)(cusparseHandle_t, int, int, float *, float *, float *, float *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgtsvInterleavedBatch(cusparseHandle_t handle, int algo, int m, float *dl, float *d, float *du, float *x, int batchCount, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgtsvInterleavedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgtsvInterleavedBatch = (cusparseStatus_t (*)(cusparseHandle_t, int, int, float *, float *, float *, float *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgtsvInterleavedBatch");
			fprintf(stderr, "wrapper_cusparseSgtsvInterleavedBatch:%p\n", wrapper_cusparseSgtsvInterleavedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgtsvInterleavedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgtsvInterleavedBatch(handle, algo, m, dl, d, du, x, batchCount, pBuffer);
		return retval;
	}
}