#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMatSetAttribute)(cusparseSpMatDescr_t, cusparseSpMatAttribute_t, void *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMatSetAttribute(cusparseSpMatDescr_t spMatDescr, cusparseSpMatAttribute_t attribute, void *data, size_t dataSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMatSetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMatSetAttribute = (cusparseStatus_t (*)(cusparseSpMatDescr_t, cusparseSpMatAttribute_t, void *, size_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMatSetAttribute");
			fprintf(stderr, "wrapper_cusparseSpMatSetAttribute:%p\n", wrapper_cusparseSpMatSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMatSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMatSetAttribute(spMatDescr, attribute, data, dataSize);
		return retval;
	}
}