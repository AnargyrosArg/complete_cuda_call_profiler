#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMatGetAttribute)(cusparseSpMatDescr_t, cusparseSpMatAttribute_t, void *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMatGetAttribute(cusparseSpMatDescr_t spMatDescr, cusparseSpMatAttribute_t attribute, void *data, size_t dataSize) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMatGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMatGetAttribute = (cusparseStatus_t (*)(cusparseSpMatDescr_t, cusparseSpMatAttribute_t, void *, size_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMatGetAttribute");
			fprintf(stderr, "wrapper_cusparseSpMatGetAttribute:%p\n", wrapper_cusparseSpMatGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMatGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMatGetAttribute(spMatDescr, attribute, data, dataSize);
		return retval;
	}
}