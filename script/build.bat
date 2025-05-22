@echo off
setlocal enabledelayedexpansion

:: 获取脚本所在目录
set "SCRIPT_DIR=%~dp0"
set "PROJECT_ROOT=%SCRIPT_DIR%\.."

:: 处理命令行参数
if "%1"=="-c" (
    echo Cleaning build directory...
    if exist "%PROJECT_ROOT%\build" rd /s /q "%PROJECT_ROOT%\build"
)

:: 创建并进入构建目录
echo Creating build directory...
if not exist "%PROJECT_ROOT%\build" mkdir "%PROJECT_ROOT%\build"
cd "%PROJECT_ROOT%\build"

:: 检测 Visual Studio 版本
where /q cl.exe
if %ERRORLEVEL% neq 0 (
    :: 尝试查找并设置 Visual Studio 环境
    if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    ) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
    ) else (
        echo Error: Visual Studio not found
        exit /b 1
    )
)

:: 运行 CMake
echo Running CMake...
cmake -G "Visual Studio 17 2022" -A x64 ..
if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed
    exit /b 1
)

:: 编译项目
echo Building project...
cmake --build . --config Release
if %ERRORLEVEL% neq 0 (
    echo Build failed
    exit /b 1
)

echo Build completed successfully!

:: 运行测试程序（如果存在）
if exist "bin\Release\test_eye.exe" (
    echo Running test program...
    "bin\Release\test_eye.exe"
)

endlocal
