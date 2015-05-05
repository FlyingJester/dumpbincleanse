# dumpbincleanse

About
=====

dumpbincleanse is a tool to help create .lib files for .dll files created with MingW and Cygwin from Visual C++. It can also be used with Visual C++ .dll files that have no .lib file included.
This only works with libraries that use C linkage. If you cannot use the library from C, you cannot use dumpbincleanse directly to use it from Visual C++.

You will need some of the basic tools from Microsoft Visual Studio to use dumpbincleanse.

Usage
=====

Assuming you compiled or recieved some library called "a.dll", you would use the MSVC tools and dumpbincleanse like this to create a .lib file:

`dumpbin /exports a.dll > a.def.raw`
`dumpbincleanse.exe a.def.raw a.def`
`lib /def:a.def /OUT:a.lib`

This will create a .lib file you can use with Visual C++. You still need to get headers for it somewhere, though :)