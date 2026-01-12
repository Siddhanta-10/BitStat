# build.ps1
$ErrorActionPreference = "Stop"

# 1. Clean/Create Build Directory
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
    Write-Host "Created build directory." -ForegroundColor Cyan
}

# 2. Configure (Generate Project Files)
Write-Host "Configuring..." -ForegroundColor Yellow
cmake -S . -B build

# 3. Build (Compile everything)
Write-Host "Building..." -ForegroundColor Yellow
cmake --build build --config Debug

# 4. Run Tests (using CTest)
Write-Host "Running Tests..." -ForegroundColor Yellow
# --output-on-failure: Shows the error log if a test crashes
# -C Debug: Tells CTest to look in the Debug folder (crucial for Visual Studio)
cd build
ctest -C Debug --output-on-failure
cd ..