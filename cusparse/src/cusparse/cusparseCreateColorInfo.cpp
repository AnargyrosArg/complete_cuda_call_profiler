#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreateColorInfo)(cusparseColorInfo_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreateColorInfo(cusparseColorInfo_t *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreateColorInfo)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreateColorInfo = (cusparseStatus_t (*)(cusparseColorInfo_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreateColorInfo");
			fprintf(stderr, "wrapper_cusparseCreateColorInfo:%p\n", wrapper_cusparseCreateColorInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreateColorInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreateColorInfo(info);
		return retval;
	}
}