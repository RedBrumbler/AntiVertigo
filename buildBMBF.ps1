# Builds a .zip file for loading with BMBF
$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk
Compress-Archive -Path "cover.png","./libs/arm64-v8a/libantivertigo.so","./bmbfmod.json","./extern/libbeatsaber-hook_0_8_4.so","./extern/libquestui.so","./extern/libcustom-types.so" -DestinationPath "./AntiVertigo.zip" -Update
