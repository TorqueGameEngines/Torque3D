# Vcpkg: Overview

[中文总览](README_zh_CN.md)
[Español](README_es.md)
[한국어](README_ko_KR.md)
[Français](README_fr.md)

Vcpkg helps you manage C and C++ libraries on Windows, Linux and MacOS.
This tool and ecosystem are constantly evolving, and we always appreciate contributions!

If you've never used vcpkg before, or if you're trying to figure out how to use vcpkg,
check out our [Getting Started](#getting-started) section for how to start using vcpkg.

For short description of available commands, once you've installed vcpkg,
you can run `vcpkg help`, or `vcpkg help [command]` for command-specific help.

* Github: [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg)
* Slack: [https://cppalliance.org/slack/](https://cppalliance.org/slack/), the #vcpkg channel
* Discord: [\#include \<C++\>](https://www.includecpp.org), the #🌏vcpkg channel
* Docs: [Documentation](docs/README.md)

[![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/microsoft.vcpkg.ci?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=29&branchName=master)

# Table of Contents

- [Vcpkg: Overview](#vcpkg-overview)
- [Table of Contents](#table-of-contents)
- [Getting Started](#getting-started)
  - [Quick Start: Windows](#quick-start-windows)
  - [Quick Start: Unix](#quick-start-unix)
  - [Installing Linux Developer Tools](#installing-linux-developer-tools)
  - [Installing macOS Developer Tools](#installing-macos-developer-tools)
    - [Installing GCC for macOS before 10.15](#installing-gcc-for-macos-before-1015)
  - [Using vcpkg with CMake](#using-vcpkg-with-cmake)
    - [Visual Studio Code with CMake Tools](#visual-studio-code-with-cmake-tools)
    - [Vcpkg with Visual Studio CMake Projects](#vcpkg-with-visual-studio-cmake-projects)
    - [Vcpkg with CLion](#vcpkg-with-clion)
    - [Vcpkg as a Submodule](#vcpkg-as-a-submodule)
- [Tab-Completion/Auto-Completion](#tab-completionauto-completion)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)
- [Telemetry](#telemetry)

# Getting Started

First, follow the quick start guide for either
[Windows](#quick-start-windows), or [macOS and Linux](#quick-start-unix),
depending on what you're using.

For more information, see [Installing and Using Packages][getting-started:using-a-package].
If a library you need is not present in the vcpkg catalog,
you can [open an issue on the GitHub repo][contributing:submit-issue]
where the vcpkg team and community can see it,
and potentially add the port to vcpkg.

After you've gotten vcpkg installed and working,
you may wish to add [tab completion](#tab-completionauto-completion) to your shell.

Finally, if you're interested in the future of vcpkg,
check out the [manifest][getting-started:manifest-spec] guide!
This is an experimental feature and will likely have bugs,
so try it out and [open all the issues][contributing:submit-issue]!

## Quick Start: Windows

Prerequisites:
- Windows 7 or newer
- [Git][getting-started:git]
- [Visual Studio][getting-started:visual-studio] 2015 Update 3 or greater with the English language pack

First, download and bootstrap vcpkg itself; it can be installed anywhere,
but generally we recommend using vcpkg as a submodule for CMake projects,
and installing it globally for Visual Studio projects.
We recommend somewhere like `C:\src\vcpkg` or `C:\dev\vcpkg`,
since otherwise you may run into path issues for some port build systems.

```cmd
> git clone https://github.com/microsoft/vcpkg
> .\vcpkg\bootstrap-vcpkg.bat
```

To install the libraries for your project, run:

```cmd
> .\vcpkg\vcpkg install [packages to install]
```

Note: This will install x86 libraries by default. To install x64, run:

```cmd
> .\vcpkg\vcpkg install package:x64-windows
```

Or

```cmd
> .\vcpkg\vcpkg install [packages to install] --triplet=x64-windows
```

You can also search for the libraries you need with the `search` subcommand:

```cmd
> .\vcpkg\vcpkg search [search term]
```

In order to use vcpkg with Visual Studio,
run the following command (may require administrator elevation):

```cmd
> .\vcpkg\vcpkg integrate install
```

After this, you can now create a New non-CMake Project (or open an existing one).
All installed libraries are immediately ready to be `#include`'d and used
in your project without additional configuration.

If you're using CMake with Visual Studio,
continue [here](#vcpkg-with-visual-studio-cmake-projects).

In order to use vcpkg with CMake outside of an IDE,
you can use the toolchain file:

```cmd
> cmake -B [build directory] -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
> cmake --build [build directory]
```

With CMake, you will still need to `find_package` and the like to use the libraries.
Check out the [CMake section](#using-vcpkg-with-cmake) for more information,
including on using CMake with an IDE.

For any other tools, including Visual Studio Code,
check out the [integration guide][getting-started:integration].

## Quick Start: Unix

Prerequisites for Linux:
- [Git][getting-started:git]
- [g++][getting-started:linux-gcc] >= 6

Prerequisites for macOS:
- [Apple Developer Tools][getting-started:macos-dev-tools]
- On macOS 10.14 or below, you will also need:
  - [Homebrew][getting-started:macos-brew]
  - [g++][getting-started:macos-gcc] >= 6 from Homebrew

First, download and bootstrap vcpkg itself; it can be installed anywhere,
but generally we recommend using vcpkg as a submodule for CMake projects.

```sh
$ git clone https://github.com/microsoft/vcpkg
$ ./vcpkg/bootstrap-vcpkg.sh
```

To install the libraries for your project, run:

```sh
$ ./vcpkg/vcpkg install [packages to install]
```

You can also search for the libraries you need with the `search` subcommand:

```sh
$ ./vcpkg/vcpkg search [search term]
```

In order to use vcpkg with CMake, you can use the toolchain file:

```sh
$ cmake -B [build directory] -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
$ cmake --build [build directory]
```

With CMake, you will still need to `find_package` and the like to use the libraries.
Check out the [CMake section](#using-vcpkg-with-cmake)
for more information on how best to use vcpkg with CMake,
and CMake Tools for VSCode.

For any other tools, check out the [integration guide][getting-started:integration].

## Installing Linux Developer Tools

Across the different distros of Linux, there are different packages you'll
need to install:

- Debian, Ubuntu, popOS, and other Debian-based distributions:

```sh
$ sudo apt-get update
$ sudo apt-get install build-essential tar curl zip unzip
```

- CentOS

```sh
$ sudo yum install centos-release-scl
$ sudo yum install devtoolset-7
$ scl enable devtoolset-7 bash
```

For any other distributions, make sure you're installing g++ 6 or above.
If you want to add instructions for your specific distro,
[please open a PR][contributing:submit-pr]!

## Installing macOS Developer Tools

On macOS 10.15, the only thing you should need to do is run the following in your terminal:

```sh
$ xcode-select --install
```

Then follow along with the prompts in the windows that comes up.

On macOS 10.14 and previous, you'll also need to install g++ from homebrew;
follow the instructions in the following section.

### Installing GCC for macOS before 10.15

This will _only_ be necessary if you're using a macOS version from before 10.15.
Installing homebrew should be very easy; check out <brew.sh> for more information,
but at its simplest, run the following command:

```sh
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
```

Then, in order to grab an up-to-date version of gcc, run the following:

```sh
$ brew install gcc
```

You'll then be able to bootstrap vcpkg along with the [quick start guide](#quick-start-unix)

## Using vcpkg with CMake

If you're using vcpkg with CMake, the following may help!

### Visual Studio Code with CMake Tools

Adding the following to your workspace `settings.json` will make
CMake Tools automatically use vcpkg for libraries:

```json
{
  "cmake.configureSettings": {
    "CMAKE_TOOLCHAIN_FILE": "[vcpkg root]/scripts/buildsystems/vcpkg.cmake"
  }
}
```

### Vcpkg with Visual Studio CMake Projects

Open the CMake Settings Editor, and under `CMake toolchain file`,
add the path to the vcpkg toolchain file:

```
[vcpkg root]/scripts/buildsystems/vcpkg.cmake
```

### Vcpkg with CLion

Open the Toolchains settings
(File > Settings on Windows and Linux, CLion > Preferences on macOS),
and go to the CMake settings (Build, Execution, Deployment > CMake).
Finally, in `CMake options`, add the following line:

```
-DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
```

Unfortunately, you'll have to add this to each profile.

### Vcpkg as a Submodule

When using vcpkg as a submodule of your project,
you can add the following to your CMakeLists.txt before the first `project()` call,
instead of passing `CMAKE_TOOLCHAIN_FILE` to the cmake invocation.

```cmake
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")
```

This will still allow people to not use vcpkg,
by passing the `CMAKE_TOOLCHAIN_FILE` directly,
but it will make the configure-build step slightly easier.

[getting-started:using-a-package]: docs/examples/installing-and-using-packages.md
[getting-started:integration]: docs/users/integration.md
[getting-started:git]: https://git-scm.com/downloads
[getting-started:cmake-tools]: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools
[getting-started:linux-gcc]: #installing-linux-developer-tools
[getting-started:macos-dev-tools]: #installing-macos-developer-tools
[getting-started:macos-brew]: #installing-gcc-on-macos
[getting-started:macos-gcc]: #installing-gcc-on-macos
[getting-started:visual-studio]: https://visualstudio.microsoft.com/
[getting-started:manifest-spec]: docs/specifications/manifests.md

# Tab-Completion/Auto-Completion

`vcpkg` supports auto-completion of commands, package names,
and options in both powershell and bash.
To enable tab-completion in the shell of your choice, run:

```pwsh
> .\vcpkg integrate powershell
```

or

```sh
$ ./vcpkg integrate bash
```

depending on the shell you use, then restart your console.

# Examples

See the [documentation](docs/README.md) for specific walkthroughs,
including [installing and using a package](docs/examples/installing-and-using-packages.md),
[adding a new package from a zipfile](docs/examples/packaging-zipfiles.md),
and [adding a new package from a GitHub repo](docs/examples/packaging-github-repos.md).

Our docs are now also available online at ReadTheDocs: <https://vcpkg.readthedocs.io/>!

See a 4 minute [video demo](https://www.youtube.com/watch?v=y41WFKbQFTw).

# Contributing

Vcpkg is an open source project, and is thus built with your contributions.
Here are some ways you can contribute:

* [Submit Issues][contributing:submit-issue] in vcpkg or existing packages
* [Submit Fixes and New Packages][contributing:submit-pr]

Please refer to our [Contributing Guide](CONTRIBUTING.md) for more details.

This project has adopted the [Microsoft Open Source Code of Conduct][contributing:coc].
For more information see the [Code of Conduct FAQ][contributing:coc-faq]
or email [opencode@microsoft.com](mailto:opencode@microsoft.com)
with any additional questions or comments.

[contributing:submit-issue]: https://github.com/microsoft/vcpkg/issues/new/choose
[contributing:submit-pr]: https://github.com/microsoft/vcpkg/pulls
[contributing:coc]: https://opensource.microsoft.com/codeofconduct/
[contributing:coc-faq]: https://opensource.microsoft.com/codeofconduct/

# License

The code in this repository is licensed under the [MIT License](LICENSE.txt).

# Telemetry

vcpkg collects usage data in order to help us improve your experience.
The data collected by Microsoft is anonymous.
You can opt-out of telemetry by re-running the bootstrap-vcpkg script with -disableMetrics,
passing --disable-metrics to vcpkg on the command line,
or by setting the VCPKG_DISABLE_METRICS environment variable.

Read more about vcpkg telemetry at docs/about/privacy.md
