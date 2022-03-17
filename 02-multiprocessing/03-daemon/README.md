# Daemon process

> Daemons are processes that live for a long time.
> They are often started when the system is bootstrapped and
> terminate only when the system is shut down.
> Because they don’t have a controlling terminal,
> we say that they run in the background.
> UNIX systems have numerous daemons that perform day-to-day activities.

## Process Group & session
```C
// get the process group ID of the calling process
pid_t getpgrp (void);

// get the process group ID for a process
pid_t getpgid (pid_t pid);

// set process group ID for job control
int   setpgid(pid_t pid, pid_t pgid);

// get the process group ID of a session leader
pid_t getsid (pid_t pid):

// creates a session and sets the process group ID
pid_t setsid (void);
```

## Daemon Process
Some basic rules to coding a daemon prevent unwanted interactions from happening.
> 1. Call umask to set the file mode creation mask to a known value, usually 0. 
> The inherited file mode creation mask could be set to deny certain permissions. 
> If the daemon process creates files, it may want to set specific permissions.

> 2. Call fork and have the parent exit. This does several things. 
> First, if the daemon was started as a simple shell command, 
> having the parent terminate makes the shell think that the command is done. 
> Second, the child inherits the process group ID of the parent 
> but gets a new process ID, 
> so we’re guaranteed that the child is not a process group leader. 
> This is a prerequisite for the call to setsid that is done next.

> 3. Call setsid to create a new session.

> 4. Change the current working directory to the root directory. 
> The current working directory inherited from the parent 
> could be on a mounted file system. 
> Since daemons normally exist until the system is rebooted, 
> if the daemon stays on a mounted file system, 
> that file system cannot be unmounted.

> 5. Unneeded file descriptors should be closed. 
> This prevents the daemon from holding open any descriptors 
> that it may have inherited from its parent 
> (which could be a shell or some other process).

> 6. Some daemons open file descriptors 0, 1, and 2 to /dev/null 
> so that any library routines 
> that try to read from standard input or write to standard output 
> or standard error will have no effect. 

## Reference
Quoted above from chpter 13 of [apue3e](http://www.apuebook.com/apue3e.html).
