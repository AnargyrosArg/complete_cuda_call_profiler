#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCooSetStridedBatch)(cusparseSpMatDescr_t, int, int64_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCooSetStridedBatch(cusparseSpMatDescr_t spMatDescr, int batchCount, int64_t batchStride) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCooSetStridedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCooSetStridedBatch = (cusparseStatus_t (*)(cusparseSpMatDescr_t, int, int64_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCooSetStridedBatch");
			fprintf(stderr, "wrapper_cusparseCooSetStridedBatch:%p\n", wrapper_cusparseCooSetStridedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCooSetStridedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCooSetStridedBatch(spMatDescr, batchCount, batchStride);
		return retval;
	}
}