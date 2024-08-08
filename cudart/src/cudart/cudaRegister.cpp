#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
extern "C"
{

extern void* libcudart_handle;

char (*wrapper___cudaInitModule)(void **);
void** (*wrapper___cudaRegisterFatBinary)(void*);
void (*wrapper___cudaRegisterFatBinaryEnd)(void** );
void (*wrapper___cudaUnregisterFatBinary)(void**);
void (*wrapper___cudaRegisterFunction)(void **fatCubinHandle, const char *hostFun, char *deviceFun, const char *deviceName, int thread_limit, uint3 *tid, uint3 *bid, dim3 *bDim, dim3 *gDim, int *wSize);
void (*wrapper___cudaRegisterVar)(void **fatCubinHandle,char  *hostVar,char  *deviceAddress,const char *deviceName,int ext,size_t size,int constant,int global);
cudaError_t (*wrapper___cudaPopCallConfiguration)(dim3 *, dim3 *, size_t *, cudaStream_t *);
cudaError_t (*wrapper___cudaPushCallConfiguration)(dim3 , dim3 , size_t , cudaStream_t );
void (*wrapper___cudaRegisterManagedVar)(void **fatCubinHandle,void **hostVarPtrAddress,char *deviceAddress,const char  *deviceName,int ext,size_t size,int constant,int global);


char __cudaInitModule(void **fatCubinHandle)
{
	#ifdef PRINT_TRACE
    fprintf(stderr,"%s()\n",__func__);
    #endif
    char* __dlerror;
	//this call clears any previous errors
	dlerror();
	if(libcudart_handle == NULL){
		libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
	}
	if (!wrapper___cudaInitModule)
	{
		//fetch the original fntion addr using dlsym
		wrapper___cudaInitModule = (char (*)(void **)) dlsym(libcudart_handle, "__cudaInitModule");
		fprintf(stderr, "cudaInitModule:%p\n", wrapper___cudaInitModule);
	}
	__dlerror = dlerror();
	if(__dlerror){
		fprintf(stderr, "dlsym error for fntion __cudaInitModule():%s\n", __dlerror);
		fflush(stderr);
	}
	return wrapper___cudaInitModule(fatCubinHandle);
}

void ** __cudaRegisterFatBinary(void **fatCubin)
{
	#ifdef PRINT_TRACE
    fprintf(stderr,"%s()\n",__func__);
    #endif
    char* __dlerror;
	//this call clears any previous errors
	dlerror();
	if(libcudart_handle == NULL){
		libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
	}
	if (!wrapper___cudaRegisterFatBinary)
	{
		//fetch the original fntion addr using dlsym
		wrapper___cudaRegisterFatBinary = (void** (*)(void*) ) dlsym(libcudart_handle, "__cudaRegisterFatBinary");
		fprintf(stderr, "__cudaRegisterFatBinary:%p\n", wrapper___cudaRegisterFatBinary);
	}
	__dlerror = dlerror();
	if(__dlerror){
		fprintf(stderr, "dlsym error for fntion wrapper___cudaRegisterFatBinary():%s\n", __dlerror);
		fflush(stderr);
	}
	return wrapper___cudaRegisterFatBinary(fatCubin);
}

void __cudaRegisterFatBinaryEnd(void **fatCubinHandle)
{
	#ifdef PRINT_TRACE
    fprintf(stderr,"%s()\n",__func__);
    #endif
    char* __dlerror;
	//this call clears any previous errors
	dlerror();
	if(libcudart_handle == NULL){
		libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
	}
	if (!wrapper___cudaRegisterFatBinaryEnd)
	{
		//fetch the original fntion addr using dlsym
		wrapper___cudaRegisterFatBinaryEnd = (void (*)(void**)) dlsym(libcudart_handle, "__cudaRegisterFatBinaryEnd");
		fprintf(stderr, "cudaRegisterFatBinaryEnd:%p\n", wrapper___cudaRegisterFatBinaryEnd);
	}
	__dlerror = dlerror();
	if(__dlerror){
		fprintf(stderr, "dlsym error for fntion wrapper___cudaRegisterFatBinaryEnd():%s\n", __dlerror);
		fflush(stderr);
	}
	wrapper___cudaRegisterFatBinaryEnd(fatCubinHandle);
}

void __cudaUnregisterFatBinary(void **fatCubin)
{
	#ifdef PRINT_TRACE
    fprintf(stderr,"%s()\n",__func__);
    #endif
    char* __dlerror;
	//this call clears any previous errors
	dlerror();
	if(libcudart_handle == NULL){
		libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
	}
	if (!wrapper___cudaUnregisterFatBinary)
	{
		//fetch the original fntion addr using dlsym
		wrapper___cudaUnregisterFatBinary = (void (*)(void **)) dlsym(libcudart_handle, "__cudaUnregisterFatBinary");
		fprintf(stderr, "cudaUnregisterFatBinary:%p\n", wrapper___cudaUnregisterFatBinary);
	}
	__dlerror = dlerror();
	if(__dlerror){
		fprintf(stderr, "dlsym error for fntion wrapper___cudaUnregisterFatBinary():%s\n", __dlerror);
		fflush(stderr);
	}
	wrapper___cudaUnregisterFatBinary(fatCubin);
}

void __cudaRegisterFunction(void **fatCubinHandle, const char *hostFun, char *deviceFun, const char *deviceName, int thread_limit, uint3 *tid, uint3 *bid, dim3 *bDim, dim3 *gDim, int *wSize)
{
	#ifdef PRINT_TRACE
    fprintf(stderr,"%s()\n",__func__);
    #endif
    char* __dlerror;
	//this call clears any previous errors
	dlerror();
	if(libcudart_handle == NULL){
		libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
	}
	if (!wrapper___cudaRegisterFunction)
	{
		//fetch the original fntion addr using dlsym
		wrapper___cudaRegisterFunction = (void (*)(void **, const char *, char *, const char *, int , uint3 *, uint3 *, dim3 *, dim3 *, int *)) dlsym(libcudart_handle, "__cudaRegisterFunction");
		fprintf(stderr, "cudaRegisterFunction:%p\n", wrapper___cudaRegisterFunction);
	}
	__dlerror = dlerror();
	if(__dlerror){
		fprintf(stderr, "dlsym error for fntion wrapper___cudaRegisterFunction():%s\n", __dlerror);
		fflush(stderr);
	}
	wrapper___cudaRegisterFunction(fatCubinHandle, hostFun, deviceFun, deviceName, thread_limit, tid, bid,bDim,gDim,wSize);
}

void __cudaRegisterVar(void **fatCubinHandle,char  *hostVar,char  *deviceAddress,  const char  *deviceName,int ext,size_t size,int constant,int global)
{
	#ifdef PRINT_TRACE
    fprintf(stderr,"%s()\n",__func__);
    #endif
    char* __dlerror;
	//this call clears any previous errors
	dlerror();
	if(libcudart_handle == NULL){
		libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
	}
	if (!wrapper___cudaRegisterVar)
	{
		//fetch the original fntion addr using dlsym
		wrapper___cudaRegisterVar = (void (*)(void **,char  *,char  *,const char *,int ,size_t ,int ,int)) dlsym(libcudart_handle, "__cudaRegisterVar");
		fprintf(stderr, "cudaRegisterVar:%p\n", __cudaRegisterVar);
	}
	__dlerror = dlerror();
	if(__dlerror){
		fprintf(stderr, "dlsym error for fntion wrapper___cudaRegisterVar():%s\n", __dlerror);
		fflush(stderr);
	}
	wrapper___cudaRegisterVar(fatCubinHandle,hostVar,deviceAddress,deviceName,ext,size,constant,global);
}

cudaError_t __cudaPopCallConfiguration(dim3 *gridDim, dim3 *blockDim, size_t *sharedMem, cudaStream_t *stream){
	#ifdef PRINT_TRACE
    fprintf(stderr,"%s()\n",__func__);
    #endif
    char* __dlerror;
	//this call clears any previous errors
	dlerror();
	if(libcudart_handle == NULL){
		libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
	}
	if (!wrapper___cudaPopCallConfiguration)
	{
		//fetch the original fntion addr using dlsym
		wrapper___cudaPopCallConfiguration = (cudaError_t (*)(dim3 *, dim3 *, size_t *, cudaStream_t *)) dlsym(libcudart_handle, "__cudaPopCallConfiguration");
		fprintf(stderr, "cudaPopCallConfiguration:%p\n", wrapper___cudaPushCallConfiguration);
	}
	__dlerror = dlerror();
	if(__dlerror){
		fprintf(stderr, "dlsym error for fntion wrapper___cudaPopCallConfiguration():%s\n", __dlerror);
		fflush(stderr);
	}
	return wrapper___cudaPopCallConfiguration(gridDim,blockDim,sharedMem,stream);
}

cudaError_t __cudaPushCallConfiguration(dim3 gridDim, dim3 blockDim, size_t sharedMem, cudaStream_t stream) {
	#ifdef PRINT_TRACE
    fprintf(stderr,"%s()\n",__func__);
    #endif
    char* __dlerror;
	//this call clears any previous errors
	dlerror();
	if(libcudart_handle == NULL){
		libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
	}
	if (!wrapper___cudaPushCallConfiguration)
	{
		//fetch the original fntion addr using dlsym
		wrapper___cudaPushCallConfiguration = (cudaError_t (*)(dim3 , dim3, size_t , cudaStream_t )) dlsym(libcudart_handle, "__cudaPushCallConfiguration");
		fprintf(stderr, "cudaPushCallConfiguration:%p\n", wrapper___cudaPushCallConfiguration);
	}
	__dlerror = dlerror();
	if(__dlerror){
		fprintf(stderr, "dlsym error for fntion wrapper___cudaPushCallConfiguration():%s\n", __dlerror);
		fflush(stderr);
	}
	return wrapper___cudaPushCallConfiguration(gridDim,blockDim,sharedMem,stream);
}




void __cudaRegisterManagedVar(void **fatCubinHandle,void **hostVarPtrAddress,char *deviceAddress,const char *deviceName,int	ext,size_t size,int	constant,int	global){
    #ifdef PRINT_TRACE
    fprintf(stderr,"%s()\n",__func__);
    #endif
	char* __dlerror;
	//this call clears any previous errors
	dlerror();
	if(libcudart_handle == NULL){
		libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
	}
	if (!wrapper___cudaRegisterManagedVar)
	{
		//fetch the original fntion addr using dlsym
		wrapper___cudaRegisterManagedVar = (void (*)(void **,void **,char *,const char *,int,size_t,int,int)) dlsym(libcudart_handle, "__cudaRegisterManagedVar");
		fprintf(stderr, "cudaRegisterManagedVar:%p\n", wrapper___cudaRegisterManagedVar);
	}
	__dlerror = dlerror();
	if(__dlerror){
		fprintf(stderr, "dlsym error for fntion wrapper___cudaRegisterManagedVar():%s\n", __dlerror);
		fflush(stderr);
	}
	return wrapper___cudaRegisterManagedVar(fatCubinHandle,hostVarPtrAddress,deviceAddress,deviceName,ext,size,constant,global);
}

}