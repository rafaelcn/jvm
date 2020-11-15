# nJVM

An implementation of (some characteristics of) the JVM in C.

# Build

Use make to compile.

# Usage

You have following options when using the nJVM:

| command | argument | description |
|---------|----------|-------------|
| help    |  - | show the help message |
| version | - | show the version information |
| debug   | - | shows more information on the output |
| execute | class filename | execute the given .class file |
| information | class filename | shows information about the .class file |

Using the commands given are shown in the following code.

```
$ ./njvm --execute hello.class

... executes the code
```

```
$ ./njvm --help

UNB JRE Version 0.1.0

usage:
	./nvjm.exe --execute <hello.class>
```

available commands:

	--help			- show this information
	--version		- show the version of the nJVM
    --debug 		- enables the debug mode that shows more information
	--execute <class file>	- executes a class file
	--inform  <class file>	- shows information about the class file


# documentation

We use doxygen to generate our documentation and you can do it by using the
following command:

`doxygen documentation.conf`