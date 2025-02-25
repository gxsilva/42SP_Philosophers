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


## Mutex
Mutex (Mutual Exclusion) is a locking mechanism used in multithreading to prevente multiple thread from acessing a shared resource at the same time.

- A _thread_ locks the mutex before acessing the shared resource.
- Other threads that tryto lock the same mutex will _wait_ until it's unlocked
- The thread _unlocks_ the mutex when it's done, allowing toher threads to proceed.

If two threads are writing to the same file at the same time, their outputs could mix and become corrupted. A mutex ensures that only one thread can write at a time
