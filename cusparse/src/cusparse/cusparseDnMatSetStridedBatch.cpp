#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDnMatSetStridedBatch)(cusparseDnMatDescr_t, int, int64_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDnMatSetStridedBatch(cusparseDnMatDescr_t dnMatDescr, int batchCount, int64_t batchStride) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDnMatSetStridedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDnMatSetStridedBatch = (cusparseStatus_t (*)(cusparseDnMatDescr_t, int, int64_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDnMatSetStridedBatch");
			fprintf(stderr, "wrapper_cusparseDnMatSetStridedBatch:%p\n", wrapper_cusparseDnMatSetStridedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDnMatSetStridedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDnMatSetStridedBatch(dnMatDescr, batchCount, batchStride);
		return retval;
	}
}