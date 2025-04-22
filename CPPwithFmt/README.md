# How to use vcpkg

Video tutorial used:
> ![](https://www.youtube.com/watch?v=3X4DmBfjy0Y)

vcpkg comes **bundled with visual studio** and accesible through the ***Developer PowerShell for VS 2022***.

To install it user-wide, run `vcpkg integrate install`. This will make it possible to integrate vcpkg with every Visual Studio C++ project placed under the current user.

To use in a given project, configure it to use vcpkg manifest:\
*Project -> Configuration Properties -> vcpkg -> Use Vcpkg Manifest*

After that, create a vcpkg manifest by running **in the project directory** `vcpkg new --application`.

To install packages run `vcpkg add port <package name>`.
