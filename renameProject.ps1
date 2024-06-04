param (
    [string]$newProjectName
)

# Check if a new project name was provided
if (-not $newProjectName) {
    Write-Host "Usage: .\rename_project.ps1 -newProjectName <NewProjectName>"
    exit 1
}

# Define the path to the CMakeLists.txt file
$cmakeFilePath = ".\CMakeLists.txt"

# Check if the CMakeLists.txt file exists
if (-not (Test-Path $cmakeFilePath)) {
    Write-Host "CMakeLists.txt not found in the current directory."
    exit 1
}

# Read the content of the CMakeLists.txt file
$cmakeContent = Get-Content $cmakeFilePath

# Replace the project name variable in the CMakeLists.txt file
$cmakeContent = $cmakeContent -replace "(?<=set\(PROJECT_NAME ).*?(?=\))", $newProjectName

# Write the updated content back to the CMakeLists.txt file
Set-Content $cmakeFilePath -Value $cmakeContent

Write-Host "PROJECT_NAME changed to $newProjectName in CMakeLists.txt."

# # Reinitialize the Git repository
# if (Test-Path .git) {
#     Remove-Item -Recurse -Force .git
#     git init
#     git add .
#     git commit -m "Reinitialize repository with new project name $newProjectName"
#     Write-Host "Git repository reinitialized."
# } else {
#     Write-Host "No Git repository found. Initializing a new one."
#     git init
#     git add .
#     git commit -m "Initialize repository with project name $newProjectName"
#     Write-Host "Git repository initialized."
# }
