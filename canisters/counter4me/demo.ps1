#######################################################################
# This is a Windows PowerShell script
#
# (-) Install icpp-pro or icpp-free in a python environment on windows
# (-) Install dfx  in wsl
# (-) In a Windows PowerShell (*):
#
#     .\demo.ps1
#
# (*) The Miniconda Powershell is highly recommended
#
#######################################################################
Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Stopping the local network in wsl"
wsl dfx stop

Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Starting the local network in wsl as a PowerShell background job"
$jobName = "counter"

# Stop the job if it already exist
# Get a list of all the background jobs with a specific name
$jobs = Get-Job -Name $jobName -ErrorAction SilentlyContinue

# Stop all the jobs
$jobs | Remove-Job

# Start the local network with redirecting error messages to output stream
$job = Start-Job -ScriptBlock { wsl dfx start --clean 2>&1 } -Name $jobName

# Display the details of the job
$job | Format-Table

# Wait for 10 seconds
Write-Host " "
Write-Host "Waiting for 10 seconds to allow the local network to start..."
Start-Sleep -Seconds 10

# Get the output of the job
$output = Receive-Job -Job $job
Write-Host $output -ForegroundColor Green

#######################################################################
Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Building the wasm with wasi-sdk"
icpp build-wasm --to-compile all
# icpp build-wasm --to-compile mine

#######################################################################
Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Deploying the wasm to a canister on the local network"
wsl --% dfx deploy

#######################################################################
Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Testing counter4me with dfx"

Write-Host "- Check initial state of counter4me:"
wsl --% dfx canister call --identity default counter4me  read_counter4me

Write-Host "- Write the initial state for counter of default identity:"
wsl --% dfx canister call --identity default counter4me write_counter4me '(10: nat64)'

Write-Host "- Verify the state change of counter4me persists:"
wsl --% dfx canister call --identity default counter4me read_counter4me

Write-Host "- Increment counter for default identity, using an update call:"
wsl --% dfx canister call --identity default counter4me inc_counter4me

Write-Host "- Verify the state change of counter4me persists:"
wsl --% dfx canister call --identity default counter4me read_counter4me

Write-Host "- Write the initial state for counter of anonymous identity:"
wsl --% dfx canister call --identity anonymous counter4me write_counter4me '(10: nat64)'

Write-Host "- Verify the state change of counter4me persists:"
wsl --% dfx canister call --identity anonymous counter4me read_counter4me

Write-Host "- Increment counter for anonymous identity, using an update call:"
wsl --% dfx canister call --identity anonymous counter4me inc_counter4me

Write-Host "- Verify the state change of counter4me persists:"
wsl --% dfx canister call --identity anonymous counter4me read_counter4me

#######################################################################
Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Running the full smoketests with pytest"
pytest --network=local

#######################################################################
Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Stopping the local network in wsl"
wsl dfx stop

#######################################################################
Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Building the Windows native debug executable with clang++"
icpp build-native --to-compile all
# icpp build-native --to-compile mine

#######################################################################
Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Running the Windows native debug executable"
.\build-native\mockic.exe