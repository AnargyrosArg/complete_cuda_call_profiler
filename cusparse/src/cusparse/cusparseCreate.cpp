#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreate)(cusparseHandle_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreate(cusparseHandle_t *handle) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreate = (cusparseStatus_t (*)(cusparseHandle_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreate");
			fprintf(stderr, "wrapper_cusparseCreate:%p\n", wrapper_cusparseCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreate(handle);
		return retval;
	}
}