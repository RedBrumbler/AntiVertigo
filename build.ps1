Param(
    [Parameter(Mandatory=$false)]
    [Switch]$clean,
    [Parameter(Mandatory=$false)]
    [Switch]$release
)

# if user specified clean, remove all build files
if ($clean.IsPresent)
{
    if (Test-Path -Path "build")
    {
        remove-item build -R
    }
}

$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

# by default, build debug
$BUILD_TYPE = "Debug"
if ($release.IsPresent)
{
    # if user specified -release, build a release object
    $BUILD_TYPE = "Release"
}

if (($clean.IsPresent) -or (-not (Test-Path -Path "build")))
{
    mkdir build
} 

cd build
$cmd = "cmake -G ""Ninja"" -DCMAKE_BUILD_TYPE=`"$BUILD_TYPE`" ../"
Invoke-Expression $cmd
& cmake --build .
cd ..
exit;