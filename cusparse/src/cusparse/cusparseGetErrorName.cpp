#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
const char * (*wrapper_cusparseGetErrorName)(
cusparseStatus_t
);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	const char * cusparseGetErrorName(cusparseStatus_t status) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGetErrorName)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGetErrorName = (const char * (*)(
			cusparseStatus_t)
			) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGetErrorName");
			fprintf(stderr, "wrapper_cusparseGetErrorName:%p\n", wrapper_cusparseGetErrorName);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGetErrorName():%s\n", __dlerror);
			fflush(stderr);
		}
		const char * retval = wrapper_cusparseGetErrorName(
		status
		);
		
		return retval;
	}
}