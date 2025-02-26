## Thread functions

?Thread?
- pthread_create -> creates a new thread.
- pthread_detach -> Marks a thread as detached(desanexado), meaning its resources are automatically freed when it finishes.
- pthread_join -> waits for a thread to finish and retrives its return value

?Mutex?
- pthread_mutex_init -> Initializes _Mutex_ (used for locking?)
- pthread_mutex_destroy -> Destroy a _Mutex_ freeing its resources.
- pthread_mutex_lock -> Locks a mutex to prevent multiple threads from acessing the same resource at the same time.
- pthread_mutex_unlock -> Unlocks a mutex, allowing other threads to acess the resource

basically pthread_t is a _long int_, it holds the number of the thread, pthread_join use the number of the thread to know what end

pthread_self -> is a function that's bring to us the value o the current thread we are in the moment

the same behvaior for the function _getpid_ that's bring to us the current value of the *process* the _gettid_ brin the current of value of the *thread*


## Mutex
Mutex (Mutual Exclusion) is a locking mechanism used in multithreading to prevente multiple thread from acessing a shared resource at the same time.

- A _thread_ locks the mutex before acessing the shared resource.
- Other threads that tryto lock the same mutex will _wait_ until it's unlocked
- The thread _unlocks_ the mutex when it's done, allowing toher threads to proceed.

If two threads are writing to the same file at the same time, their outputs could mix and become corrupted. A mutex ensures that only one thread can write at a time

the correct moment to destroy the mutex wit _pthread_mutex_destroy_ is after
all _pthread_join_ are done.