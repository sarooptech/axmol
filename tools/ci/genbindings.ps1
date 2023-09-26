$myRoot = $PSScriptRoot

$llvm_ver = '15.0.7'

$AX_ROOT = (Resolve-Path $myRoot/../..).Path
$env:AX_ROOT = $AX_ROOT

# Store env path
$storedEnvPath = $env:Path

(Get-Command python.exe).Path
python -V

pip install PyYAML Cheetah3

## setup ndk
$setup_script = (Resolve-Path $AX_ROOT/setup.ps1).Path

. $setup_script -p android

echo "$ndk_root=$ndk_root"

$prefix = Join-Path $AX_ROOT 'tmp'
$llvm_out = Join-Path $prefix "llvmorg-$llvm_ver.zip"

## download win64 libclang.dll 
curl -L "https://github.com/axmolengine/buildware/releases/download/llvmorg-$llvm_ver/llvmorg-$llvm_ver.zip" -o "$llvm_out"
Expand-Archive -Path "$llvm_out" -DestinationPath $prefix
Copy-Item "$prefix/llvmorg-$llvm_ver/llvm/prebuilt/windows/x64/libclang.dll" -Destination "$AX_ROOT/tools/bindings-generator/libclang"

## ensure $env:AX_ROOT/core/axmolver.h exists
echo "AX_ROOT=$AX_ROOT"
if (!(Test-Path "$AX_ROOT/core/axmolver.h" -PathType Leaf)) {
    Copy-Item "$AX_ROOT/core/axmolver.h.in" -Destination "$AX_ROOT/core/axmolver.h"
}

## run genbindings.py
Push-Location $AX_ROOT/tools/tolua

python genbindings.py --ndk_root "$ndk_root"

$env:Path = $storedEnvPath
Pop-Location
