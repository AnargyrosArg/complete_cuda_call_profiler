#include <dlfcn.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

#define BUFSIZE 512

char* get_dyncuda_path(char*);

//pointer for original dlopen
void* (*original_dlopen)(const char *filename, int flag);

//handle for dyncuda's libcuda library
void* dyncuda_libcuda_handle = NULL;

void* libdlopen_handle = NULL;

extern "C"{
    void* __libc_dlopen_mode (const char*,int); 

    void *dlopen(const char *filename, int flag){
        char* error;
        void* retval;

        char dyncuda_libcuda_path[BUFSIZE+sizeof("/lib/libcuda_intercept.so")];
        get_dyncuda_path(dyncuda_libcuda_path);
        strcat(dyncuda_libcuda_path,"/lib/libcuda_intercept.so");


        //this call potentially clears previous errors that might have occured with dlopen,dlsym or dlclose
        dlerror();

        //get pointer to original dlopen function if not already fetched
        if(!original_dlopen){
    	    original_dlopen = (void* (*)(const char*,int)) dlsym(__libc_dlopen_mode("libdl.so.2",RTLD_LAZY), "dlopen");
            error = dlerror();
            if(error){
                fprintf(stderr,"Error occured while dlsym-ing dlopen: %s\n original_dlopen:%p\n",error,original_dlopen);
                exit(-1);
            }
        }
        if(libdlopen_handle == NULL){
            libdlopen_handle = original_dlopen("libdlopen.so",RTLD_NOW | RTLD_GLOBAL);
            error = dlerror();
            if(error){
                fprintf(stderr,"Cannot find intercept library: %s\n",error);
                exit(-1);
            }
        }

        //detect when a library attempts to load libcuda and instead, return our own.
        if(filename && (strcmp(filename,"libcuda.so.1")==0)){
            //return our own lib instead
            if(dyncuda_libcuda_handle == NULL)
                dyncuda_libcuda_handle = original_dlopen(dyncuda_libcuda_path,RTLD_NOW | RTLD_GLOBAL);

            retval = dyncuda_libcuda_handle;
            error = dlerror();
            if(error){
                fprintf(stderr,"%s\n",error);
                exit(-1);
            }
        }
        else{
            retval =  original_dlopen(filename,flag);
        }


        //its important not to exit even after getting an error as a lot of programs use try/except blocks
        //to check if some library can be found,and resume normal execution 
        error = dlerror();
        if(error) fprintf(stderr,"Error occured dlopen: %s\n retval:%p\n",error,retval);
        
        // fprintf(stderr,"handle returned for %s -> %p\n",filename,retval);
        return retval;
    }
}



char* get_dyncuda_path(char* path){
    char envvar[] = "DYNAMIC_CUDA_PATH";

    // Make sure envar actually exists
    if(!getenv(envvar)){
        fprintf(stderr, "The environment variable %s was not found.\n", envvar);
        exit(1);
    }

    // Make sure the buffer is large enough to hold the environment variable
    // value. 
    if(snprintf(path, BUFSIZE, "%s", getenv(envvar)) >= BUFSIZE){
        fprintf(stderr, "BUFSIZE of %d was too small. Aborting\n", BUFSIZE);
        exit(1);
    }

    return path;
}
