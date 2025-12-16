@echo off
setlocal

set EMSDK_QUIET=1
call emsdk_env.bat

REM Create build directory
if not exist build (
    mkdir build
)

REM Compile project
em++ main.cpp ^
    imgui/imgui.cpp ^
    imgui/imgui_draw.cpp ^
    imgui/imgui_widgets.cpp ^
    imgui/imgui_tables.cpp ^
    imgui/backends/imgui_impl_glfw.cpp ^
    imgui/backends/imgui_impl_opengl3.cpp ^
    -s USE_GLFW=3 ^
    -s FULL_ES3=1 ^
    -s WASM=1 ^
    -O2 ^
    -o build/index.js

echo Build finished! All files are in the 'build' directory.
pause
