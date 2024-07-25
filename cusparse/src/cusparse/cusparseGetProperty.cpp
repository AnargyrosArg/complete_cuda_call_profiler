#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseGetProperty)(libraryPropertyType, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseGetProperty(libraryPropertyType type, int *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGetProperty)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGetProperty = (cusparseStatus_t (*)(libraryPropertyType, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGetProperty");
			fprintf(stderr, "wrapper_cusparseGetProperty:%p\n", wrapper_cusparseGetProperty);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGetProperty():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseGetProperty(type, value);
		return retval;
	}
}