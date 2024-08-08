#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMatGetStridedBatch)(cusparseSpMatDescr_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMatGetStridedBatch(cusparseSpMatDescr_t spMatDescr, int *batchCount) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMatGetStridedBatch)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMatGetStridedBatch = (cusparseStatus_t (*)(cusparseSpMatDescr_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMatGetStridedBatch");
			fprintf(stderr, "wrapper_cusparseSpMatGetStridedBatch:%p\n", wrapper_cusparseSpMatGetStridedBatch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMatGetStridedBatch():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMatGetStridedBatch(spMatDescr, batchCount);
		return retval;
	}
}