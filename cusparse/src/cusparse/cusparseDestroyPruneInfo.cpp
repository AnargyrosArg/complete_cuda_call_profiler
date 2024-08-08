#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyPruneInfo)(pruneInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyPruneInfo(pruneInfo_t info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyPruneInfo)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyPruneInfo = (cusparseStatus_t (*)(pruneInfo_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyPruneInfo");
			fprintf(stderr, "wrapper_cusparseDestroyPruneInfo:%p\n", wrapper_cusparseDestroyPruneInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyPruneInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyPruneInfo(info);
		return retval;
	}
}