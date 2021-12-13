Param(
    [Parameter(Mandatory=$false)]
    [Switch]$release
)

$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

# by default, build debug
$BUILD_TYPE = "Debug"
if ($release.IsPresent)
{
    # if user specified -release, build a release object
    $BUILD_TYPE = "Release"
}

mkdir build
qpm qmod build
cd build
$cmd = cmake -G "Ninja" -DCMAKE_BUILD_TYPE=`"$BUILD_TYPE`" ../
cmake --build
cd ..
exit;

$buildScript = "$NDKPath/build/ndk-build"

$OS = $PSVersionTable.OS
if ($OS)
{
    $windows = $OS.Contains("Windows")
}
else
{
    $windows = 'True'
}

# when core, or when on windows we want to add .cmd to the end
if ((-not ($PSVersionTable.PSEdition -eq "Core")) -or $windows) {
    $buildScript += ".cmd"
}
$coreCount = 0
#get amount of processors
# if on a windows system
if ($windows)
{
    $prop = WMIC CPU Get NumberOfCores 
    
    $coreCount = $prop.split('\n')[2]
    $coreCount = $coreCount.Trim()
}
# if on a linux system
else
{
    $coreCount = & nproc
}
# if all fails, just assume 4
if (-not $coreCount)
{
    echo "Couldn't get core count, assuming 4"
    $coreCount = 4
}

$msg = "Building with " + $coreCount + " Cores!"
echo $msg
if ($p1 -eq "clean")
{
    echo "Removing obj dir for clean build"
    remove-item ./obj -Recurse
}

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk -j $coreCount -Oline

if (-not ($LastExitCode -eq 0)) {
    $msg = "exit code " + $LastExitCode
    echo $msg
    exit $LastExitCode
}