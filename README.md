# stubwatch

This is a way to run [Boot][bootclj] or any program that adds [inotify][inotify] watches willy-nilly on [CircleCI][circleci] without getting this error:

    User limit of inotify watches reached
    
The trick is using [LD_PRELOAD][ld_preload] to stub out [inotify_add_watch(2)][add_watch] system calls. Since this stubs out functionality, if you use this, your program won't respond to filesystem changes anymore.

## Building

    make
    
That should create a `stubwatch.o` file.

## Using

    LD_PRELOAD=/path/to/stubwatch.o boot some-task

[circleci]: https://circleci.com/
[bootclj]: http://boot-clj.com/
[ld_preload]: https://jvns.ca/blog/2014/11/27/ld-preload-is-super-fun-and-easy/
[add_watch]: https://linux.die.net/man/2/inotify_add_watch
[inotify]: https://en.wikipedia.org/wiki/Inotify
