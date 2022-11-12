# Welcome

![Screenshot](/res/screenshot1.png)

# How to build (Linux 32-bit binary on Linux)
This build uses DirectX 11 through the [dxvk-native](https://github.com/Joshua-Ashton/dxvk-native) project. CMake will automatically download and build the sources.

    git clone https://github.com/rrika/cdcEngineDXHR.git
    cd cdcEngineDXHR
    mkdir native_build
    cd native_build
    cmake .. -DNATIVE_BUILD=ON
    make
   
# How to build (Windows 32-bit binary on Linux)
This build requires the Windows SDK. There exists a Rust tool named [xwin](https://jake-shadle.github.io/xwin/) that can download it on non-windows systems. See the [rustup instructions](https://rustup.rs/) for how to install Rust. Once that is done you can build and run xwin.

    cargo install xwin --locked
    xwin --accept-license --arch x86 splat
    mv .xwin-cache/splat winsdk # need this specific folder name
    # rm -rf .xwin-cache # if you want

The CMake build of this project expects to be in a directory adjacent to `winsdk`.

    git clone https://github.com/rrika/cdcEngineDXHR.git
    cd cdcEngineDXHR
    mkdir build
    cd build
    cmake ..
    make

# How to build (Windows 32-bit binary on Windows)
In Visual Studio 2019 choose "Open a local folder" on start-up. VS should detect the CMakeLists.txt file and set up the build for you. Be sure to select x86, not x64.

# How to run
This project requires a copy of Deus Ex: Human Revolution Director's Cut to run. In the installation location you will find a number of files:

    BIGFILE.000
    BIGFILE.001
    BIGFILE.002
    ...
    DXHRDC.exe

Run the binary as follows:

    export BIGFILE=path/to/game/BIGFILE.000
    ./dxhr     # for linux build
    ./dxhr.exe # for windows build

In Visual Studio you can [set the environment](https://stackoverflow.com/questions/100543/) to `BIGFILE=C:/path/to/game/BIGFILE.000` in the project properties.
