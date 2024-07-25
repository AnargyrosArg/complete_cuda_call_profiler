#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyColorInfo)(cusparseColorInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyColorInfo(cusparseColorInfo_t info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyColorInfo)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyColorInfo = (cusparseStatus_t (*)(cusparseColorInfo_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyColorInfo");
			fprintf(stderr, "wrapper_cusparseDestroyColorInfo:%p\n", wrapper_cusparseDestroyColorInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyColorInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyColorInfo(info);
		return retval;
	}
}