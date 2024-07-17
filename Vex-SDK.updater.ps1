# Define the URL of the GitHub API for the latest release
$apiUrl = "https://api.github.com/repos/RanchoDVT/Vex-SDK/releases/latest"
$localVersionFile = "$env:APPDATA\vex_sdk_version.txt"
$zipDownloadUrl = "https://github.com/RanchoDVT/Vex-SDK/archive/refs/heads/dev.zip"
$zipFilePath = "$env:TEMP\dev.zip" # Fallback
$extractPath = "$env:TEMP\Vex-SDK-dev"# Fallback
$templatePath = "$env:USERPROFILE\.vscode-insiders\extensions\vexrobotics.vexcode-0.6.0\resources"
$VscodeInsiders = "$env:APPDATA\Code - Insiders\User\globalStorage\vexrobotics.vexcode"
$VscodeStable = "$env:APPDATA\Code\User\globalStorage\vexrobotics.vexcode"
$DesktopPath = [Environment]::GetFolderPath("Desktop")

# Function to get the latest release version from GitHub
function Get-LatestReleaseVersion {
    param ([string]$url)

    $response = Invoke-RestMethod -Uri $url -Headers @{ "User-Agent" = "PowerShell" }
    $latestTag = $response.tag_name
    return $latestTag
}

# Function to restart the script with a new version in PowerShell ISE
function Restart-Script {
    param ([string]$newScriptPath)
    
    Write-Output "A new version of the script is detected. Powershell ISE will open. Click the green run button at the top."
    
    # Open the new script in PowerShell ISE
    Start-Process -FilePath "powershell_ise.exe" -ArgumentList "`"$newScriptPath`"" -NoNewWindow

    # Wait for the ISE process to start
    Start-Sleep -Seconds 2

    # Start the new script task in ISE
    $script = @"
`$psISE.CurrentPowerShellTab.Files.Add(`"$newScriptPath`")
`$psISE.CurrentPowerShellTab.Files[`$psISE.CurrentPowerShellTab.Files.Count-1].Editor.Text = Get-Content -Path `"$newScriptPath`" -Raw
"@

    Invoke-Expression $script
    
    exit
}

# Get the latest release version, zip download URL, and commit ID
$latestVersion = Get-LatestReleaseVersion -url $apiUrl

# Read the local version
if (Test-Path -Path $localVersionFile) {
    $localVersion = Get-Content -Path $localVersionFile
} else {
    $localVersion = "0.0.0"
}

# Compare versions
if ($latestVersion -ne $localVersion) {
    Write-Output "A new version ($latestVersion) is available. Current version is $localVersion."
    $confirmation = Read-Host "Do you want to download and install the update? (y/n)"

    if ($confirmation -eq 'y') {
        # Display the process details and prompt for confirmation to kill VSCode
        Write-Output "Save your work in VsCode. We need to kill it to update the files."
        $confirmation = Read-Host "Are you sure you have saved your work? (y/n)"

        if ($confirmation -eq 'y') {
            if (Test-Path -Path $VscodeInsiders) {
                $destinationPath = $VscodeInsiders
                Stop-Process -Name "Code - Insiders" -Force -ErrorAction SilentlyContinue
            }
            elseif (Test-Path -Path $VscodeStable) {
                $destinationPath = $VscodeStable
                Stop-Process -Name "Code" -Force -ErrorAction SilentlyContinue
            }
            else {
                throw "VSCode or the VEX Robotics extension is not installed. Stopping..."
            }

            # Download the latest ZIP file
            Invoke-WebRequest -Uri $zipDownloadUrl -OutFile $zipFilePath -TimeoutSec 600

            # Extract the ZIP file
            Expand-Archive -Path $zipFilePath -DestinationPath $extractPath -Force

            # Check if the script has been updated
            $extractedScriptPath = "$extractPath\Vex-SDK-dev\Vex-SDK.updater.ps1"

            if (Test-Path -Path $extractedScriptPath) {
                $currentScriptPath = $MyInvocation.MyCommand.Path
                $currentScriptModified = (Get-Item -Path $currentScriptPath).LastWriteTime
                $extractedScriptModified = (Get-Item -Path $extractedScriptPath).LastWriteTime

                    Restart-Script -newScriptPath $extractedScriptPath
                
            }

            # Remove existing folders
            Remove-Item -Path "$destinationPath\sdk" -Recurse -Force
            Remove-Item -Path "$destinationPath\tools" -Recurse -Force
            Remove-Item -Path "$templatePath\templates" -Recurse -Force

            # Move the extracted folders to the destination path
            Move-Item -Path "$extractPath\Vex-SDK-dev\sdk" -Destination $destinationPath -Force
            Move-Item -Path "$extractPath\Vex-SDK-dev\tools" -Destination $destinationPath -Force
            Move-Item -Path "$extractPath\Vex-SDK-dev\example" -Destination $DesktopPath -Force
            Move-Item -Path "$extractPath\Vex-SDK-dev\templates" -Destination "$templatePath" -Force

            # Save the new version and commit ID
            "$latestVersion" | Set-Content -Path $localVersionFile

            # Clean up
            Remove-Item -Path $zipFilePath -Force
            Remove-Item -Path $extractPath -Recurse -Force
            
            Clear-Host
            Write-Output "Files have been successfully updated to version $latestVersion."
            Read-Host -Prompt "Press any key to exit"
        } else {
            Clear-Host
            Write-Output "Update cancelled."
            Read-Host -Prompt "Press any key to exit"
        }
    } else {
        Clear-Host
        Write-Output "Update cancelled."
        Read-Host -Prompt "Press any key to exit"
    }
} else {
    Clear-Host
    Write-Output "You already have the latest version ($localVersion)."
    Read-Host -Prompt "Press any key to exit"
}
