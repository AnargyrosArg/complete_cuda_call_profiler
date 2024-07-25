// #include <cusparse.h>
// #include <dlfcn.h>
// #include <iostream>
// void (*wrapper_cusparseLoggerCallback_t)(int, const char *, const char *);
// //handle to the libwrapper library, used to fetch original functions with dlsym
// extern void* libwrapper_cusparse_handle;
// extern "C"
// {
// 	void cusparseLoggerCallback_t(int logLevel, const char *functionName, const char *message) {
// 		char* __dlerror;
// 		//this call clears any previous errors
// 		dlerror();
// 		if(libwrapper_cusparse_handle == NULL){
// 			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
// 		}
// 		if (!wrapper_cusparseLoggerCallback_t)
// 		{
// 			//fetch the original function addr using dlsym
// 			wrapper_cusparseLoggerCallback_t = (void (*)(int, const char *, const char *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseLoggerCallback_t");
// 			fprintf(stderr, "wrapper_cusparseLoggerCallback_t:%p\n", wrapper_cusparseLoggerCallback_t);
// 		}
// 		__dlerror = dlerror();
// 		if(__dlerror){
// 			fprintf(stderr, "dlsym error for function cusparseLoggerCallback_t():%s\n", __dlerror);
// 			fflush(stderr);
// 		}
// 		wrapper_cusparseLoggerCallback_t(logLevel, functionName, message);
// 	}
// }