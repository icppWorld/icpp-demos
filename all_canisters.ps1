#######################################################################
# This is a Windows PowerShell script, 
#
# (-) equivalent to the Makefile target `all-canisters:
# (-) In a Windows PowerShell (*):
#
#     .\all_canisters.ps1
#
# (*) The Miniconda Powershell is highly recommended
#
#######################################################################

wsl --% dfx identity use default

Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Testing canisters\api_reference"
Set-Location -Path .\canisters\api_reference
.\demo.ps1

Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Testing canisters\counter"
Set-Location -Path ..\counter
.\demo.ps1

Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Testing canisters\counter4me"
Set-Location -Path ..\counter4me
.\demo.ps1

Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Testing canisters\counters"
Set-Location -Path ..\counters
.\demo.ps1

Write-Host " "
Write-Host "--------------------------------------------------"
Write-Host "Testing canisters\icpp_llama2"
Set-Location -Path ..\icpp_llama2
.\demo.ps1

# Change directory back to the root
Set-Location -Path ..\..