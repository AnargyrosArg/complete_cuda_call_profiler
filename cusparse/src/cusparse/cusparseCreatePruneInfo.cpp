#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreatePruneInfo)(pruneInfo_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreatePruneInfo(pruneInfo_t *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreatePruneInfo)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreatePruneInfo = (cusparseStatus_t (*)(pruneInfo_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreatePruneInfo");
			fprintf(stderr, "wrapper_cusparseCreatePruneInfo:%p\n", wrapper_cusparseCreatePruneInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreatePruneInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreatePruneInfo(info);
		return retval;
	}
}