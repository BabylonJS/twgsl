# twgsl

twgsl (from "to WGSL") is a small "adapter" layer exposing the
SPIR-V to WGSL transpilation capabilities of Google's 
[Tint](https://dawn.googlesource.com/tint) library to JavaScript.

## Building twgsl

I recommend building from a Linux VM set up explicitly for this purpose.

1.  [Set up Emscripten](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended),
    making sure to add its tools to your path.
1.  [Set up Chrome Depot Tools](http://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up),
    making sure to add the tools to your path.
1.  Clone twgsl and download the Tint submodule.
    ```
    git clone https://github.com/BabylonJS/twgsl.git
    cd twgsl
    git submodule update --init --recursive
    ```
1.  [Set up the Tint repository](https://dawn.googlesource.com/tint#getting-source-dependencies) 
    to build.
    ```
    cd Dependencies/Tint
    cp standalone.gclient .gclient
    gclient sync
    ```
1.  Create a build folder outside the `twgsl` folder (assumed in this 
    example to be adjacent), then configure cmake using Emscripten's CMake 
    wrapper.
    ```
    mkdir twgsl_build
    cd twgsl_build
    emcmake cmake ../twgsl
    ```
1.  Build the `twgsl` target using Emscripten's Make wrapper.
    ```
    emmake make twgsl
    ```
    Significant optimizations are turned on, so this build may take a _very_
    long time.