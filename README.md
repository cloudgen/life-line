# life-line
Life-line is a basic docker image with data folder with persistency, build with command powered by d-master

## Installation of d-master

You needed to install d-master before any operation, especially for building the docker image file:
```
./d-master self-install
```

## Build

The following is the build command

```Shell
d-master -p:Alpine-3.16 build
```

You can use the following profile such as:
 * Alpine-3.16
 * Alpine-3.17
 * Alpine-3.18
 * Debian-10
 * Debian-11
 * Debain-12
 * Centos-7
 * Centos-8
 * Centos-9
 * Ubuntu-18.04
 * Ubuntu-18.10
 * Ubuntu-19.04
 * Ubuntu-19.10
 * Ubuntu-20.04
 * Ubuntu-20.10
 * Ubuntu-21.04
 * Ubuntu-21.10
 * Ubuntu-22.04
 * Ubuntu-22.10
 * Ubuntu-23.04

## Run The Container

### Create and Run The Container
Create the container
```Shell
d-master -p:Alpine-3.16 run
```


### Execution of the shell
```
d-master -p:Alpine-3.16 exec
```

