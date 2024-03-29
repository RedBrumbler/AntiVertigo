param (
    [Parameter(Mandatory=$false)]
    [Switch]$debug_so,
    [Parameter(Mandatory=$false)]
    [Switch]$log
)

& $PSScriptRoot/build.ps1
if (-not ($LastExitCode -eq 0)) {
    echo "build failed, not copying"
    exit
}

if ($debug_so.IsPresent) {
    & adb push build/debug/libantivertigo.so /sdcard/Android/data/com.beatgames.beatsaber/files/mods/libantivertigo.so
} else {
    & adb push build/libantivertigo.so /sdcard/Android/data/com.beatgames.beatsaber/files/mods/libantivertigo.so
}

& adb shell am force-stop com.beatgames.beatsaber
& adb shell am start com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
if ($log.IsPresent) {
    & $PSScriptRoot/log.ps1
}