Matt_daemon
=====

This **42 project** is an introduction of _Daemons_.

In this project I had to create my own daemon, in **C++ 17**, that opens and listen on the port 4242 to log all the received messages into a dedicated log file.

Final grade: **100/100**.

## How to build it ?

### Prerequisite

This project has been built on my own computer and hasn't been tested on any other computer.

I'm using **Ubuntu 22.04.1 LTS** for an Intel x86_64.

You'll also need to install:
- `make` (my version is **4.3**)
- `clang++` (version: **14.0.0-1ubuntu1**)

You'll also need `figlet` & `lolcat` to get pretty outputs during build.

### Build

To build it, it will be as simple as typing `make`.

## How to run it ?

To run it, You'll have to execute the binary `Matt_daemon` with root permission granted:

```sh
$ sudo ./Matt_daemon
```

This will run a process in background, that will run a server listening on `localhost:4242`. This process will log all the incomming message in a log file: `/var/log/matt_daemon/matt_daemon.log`.

You'll be able to connect up to 3 clients to this server, by using the `nc` command as:
```sh
$ nc localhost 4242
```

You can also, see the logs, by typing:
```sh
$ tail -f /var/log/matt_daemon/matt_daemon.log
```

To kill the daemon, you can either send a `quit` message with a connected client, or send a signal to the `pid` (except `SIGKILL`).