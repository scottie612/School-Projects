
$input=$null
$ASSOCIATION_PCS=(Get-ADComputer -Filter * -SearchBase "OU=Deploy EEPC,OU=Laptops,OU=Workstations,OU=Association,OU=FACC,DC=flclerks,DC=local").name
$TEST_GROUP_PCS=(Get-ADComputer -Filter * -SearchBase "OU=TEST,OU=Deploy EEPC,OU=Laptops,OU=Workstations,OU=Service Group,OU=FACC,DC=flclerks,DC=local").name
$SDU_PCs=(Get-ADComputer -Filter * -SearchBase "OU=Laptops,OU=Workstations,OU=SDU,OU=FACC,DC=flclerks,DC=local").name
$SERVICE_GROUP_PCS=(Get-ADComputer -Filter * -SearchBase "OU=Deploy EEPC,OU=Laptops,OU=Workstations,OU=Service Group,OU=FACC,DC=flclerks,DC=local").name



While($input -ne 'q'){
    Write-Host "
============================================
Chocolatey Menu
1:--- Upgrade Single Computer
2:--- Upgrade Domain Group
3:--- Install Chocolatey on Single Computer
4:--- Install Chocolatey on Domain Group
5:--- List Programs on Computer
6:--- Install program(s) on computer(s)
q:--- Quit
============================================
    "
    $input = read-host -Prompt "Enter prompt"
    if($input -eq '1'){
        $Computer = read-host -Prompt "Enter Computer Name"
        Write-Host "===================================================== $Computer ====================================================="
        $testcon=Test-Connection $Computer -Quiet
        if($testcon -eq "True"){
            Invoke-Command -ComputerName $Computer -ScriptBlock{choco upgrade -y all}   
        }Else{
            Write-warning "$Computer IS OFFLINE"
        }
    }
    if($input -eq '2'){
        Write-Host "
============================================
PICK DOMAIN GROUP
A:--- Association Group
B:--- SDU
C:--- Service Group
D:--- Test Group    
============================================
        "
        $Group=read-host -prompt "Group Letter"
        if($Group -eq 'a'){
            write-host "Association"
            foreach($pc in $ASSOCIATION_PCS){
                Write-Host "===================================================== $pc ====================================================="
                $testcon=Test-Connection $pc -Quiet
                if($testcon -eq "True"){
                    Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y all}
                }Else{
                    Write-warning "$pc IS OFFLINE"
                }
            }
        }
        if($Group -eq 'b'){
            write-host "SDU"
            foreach($pc in $SDU_PCS){
                Write-Host "===================================================== $pc ====================================================="
                $testcon=Test-Connection $pc -Quiet
                if($testcon -eq "True"){
                    Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y all}
                }Else{
                    Write-warning "$pc IS OFFLINE"
                }
            }
        }
        if($Group -eq 'c'){
            write-host "Service Group"
            foreach($pc in $SERVICE_GROUP_PCS){
                Write-Host "===================================================== $pc ====================================================="
                $testcon=Test-Connection $pc -Quiet
                if($testcon -eq "True"){
                    Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y all}
                }Else{
                    Write-warning "$pc IS OFFLINE"
                }
            }
        }
        if($Group -eq 'd'){
            write-host "Test Group"
            foreach($pc in $TEST_GROUP_PCS){
                Write-Host "===================================================== $pc ====================================================="
                $testcon=Test-Connection $pc -Quiet
                if($testcon -eq "True"){
                    Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y all}
                }Else{
                    Write-warning "$pc IS OFFLINE"
                }
            }
        }
    }
    if($input -eq '3'){
        $Computer = read-host -Prompt "Enter Computer Name"
        Write-Host "===================================================== $Computer ====================================================="
        $testcon=Test-Connection $Computer -Quiet
        if($testcon -eq "True"){
             Invoke-Command -ComputerName $Computer -ScriptBlock{
             Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))}        
        }Else{
              Write-warning "$Computer IS OFFLINE"
        }
    }
    if($input -eq '4'){
        Write-Host "
============================================
PICK DOMAIN GROUP
A:--- Association Group
B:--- SDU
C:--- Service Group
D:--- Test Group
============================================
        "
        $Group=read-host -prompt "Group Letter"
     
        if($Group -eq 'a'){
            write-host "Association"
            foreach($pc in $ASSOCIATION_PCS){
                Write-Host "===================================================== $pc ====================================================="
                $testcon=Test-Connection $pc -Quiet
                if($testcon -eq "True"){
                    Invoke-Command -ComputerName $pc -ScriptBlock{
                    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
                }
                }Else{
                    Write-warning "$pc IS OFFLINE"
                }
            }
        }
        if($Group -eq 'b'){
            write-host "SDU"
            foreach($pc in $SDU_PCS){
                Write-Host "===================================================== $pc ====================================================="
                $testcon=Test-Connection $pc -Quiet
                if($testcon -eq "True"){
                    Invoke-Command -ComputerName $pc -ScriptBlock{
                    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
                }
                }Else{
                    Write-warning "$pc IS OFFLINE"
                }
            }
        }
        if($Group -eq 'c'){
            write-host "Service Group"
            foreach($pc in $SERVICE_GROUP_PCS){
                Write-Host "===================================================== $pc ====================================================="
                $testcon=Test-Connection $pc -Quiet
                if($testcon -eq "True"){
                    Invoke-Command -ComputerName $pc -ScriptBlock{
                    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
                }
                }Else{
                    Write-warning "$pc IS OFFLINE"
                }
            }
        }
        if($Group -eq 'd'){
            write-host "Test Group"
            foreach($pc in $TEST_GROUP_PCS){
                Write-Host "===================================================== $pc ====================================================="
                $testcon=Test-Connection $pc -Quiet
                if($testcon -eq "True"){
                    Invoke-Command -ComputerName $pc -ScriptBlock{
                    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
                }
                }Else{
                    Write-warning "$pc IS OFFLINE"
                }
            }
        }
    }
    if($input -eq '5'){
        $Computer = read-host -Prompt "Enter Computer Name"
        Invoke-Command -ComputerName $Computer -ScriptBlock{choco List -li}
    }
    if($input -eq '6'){
        
        Write-Host "
============================================
PICK AN OPTION
Default programs are read in from a text documen
A:--- Install single program on computer
B:--- Install single program on Domain Group
C:--- Install default programs on computer
D:--- Install default programs on Domain Group
============================================
        "
        $option= read-host -Prompt "Enter prompt"
        if($option -eq 'a'){
            $programname= read-host -Prompt "Enter Program Name"
            $Computer = read-host -Prompt "Enter Computer Name"
            Invoke-Command -ComputerName $Computer -ScriptBlock{choco upgrade $Using:programname -y}
        }
        if($option -eq 'b'){
                $programname= read-host -Prompt "Enter Program Name"
                Write-Host "
============================================
PICK DOMAIN GROUP
A:--- Association Group
B:--- SDU
C:--- Service Group
D:--- Test Group
============================================
        "
            $Group=read-host -prompt "Group Letter"
     
            if($Group -eq 'a'){
            write-host "Association"
                foreach($pc in $ASSOCIATION_PCS){
                    Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y $Using:programname}
                }
            }
            if($Group -eq 'b'){
                 write-host "SDU"
                foreach($pc in $SDU_PCS){
                    Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y $Using:programname}
                }
            }
            if($Group -eq 'c'){
                write-host "Service Group"
                foreach($pc in $SERVICE_GROUP_PCS){
                    Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y $Using:programname}
                }
            }
            if($Group -eq 'd'){
                write-host "Test Group"
                foreach($pc in $TEST_GROUP_PCS){
                    Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y $Using:programname}
                }
            }
        }
        if($option -eq 'c'){
            $file =Join-Path $PSScriptRoot "Default_Programs.txt"
            [string[]]$arrayFromFile = Get-Content -Path $file
            Write-Host "DEFAULT PROGRAMS TO BE INSTALLED"
            foreach($program in $arrayFromFile){Write-host $program}
             
            $Computer = read-host -Prompt "Enter Computer Name"
            foreach($program in $arrayFromFile){
                Invoke-Command -ComputerName $Computer -ScriptBlock{choco upgrade -y $Using:program}
            }
             
        }
        if($option -eq 'd'){
            $file =Join-Path $PSScriptRoot "Default_Programs.txt"
            [string[]]$arrayFromFile = Get-Content -Path $file
            Write-Host "DEFAULT PROGRAMS TO BE INSTALLED"
            foreach($program in $arrayFromFile){Write-host $program}
            Write-Host "
============================================
PICK DOMAIN GROUP
A:--- Association Group
B:--- SDU
C:--- Service Group
D:--- Test Group
============================================
        "
            $Group=read-host -prompt "Group Letter"
     
            if($Group -eq 'a'){
            write-host "Association"
                foreach($pc in $ASSOCIATION_PCS){
                    Write-Host "===================================================== $pc ====================================================="
                    $testcon=Test-Connection $pc -Quiet
                    if($testcon -eq "True"){
                        foreach($program in $arrayFromFile){
                            Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y $Using:program}
                        }
                    }Else{
                        Write-warning "$pc IS OFFLINE"
                    }
                }
            }
            if($Group -eq 'b'){
                 write-host "SDU"
                foreach($pc in $SDU_PCS){
                    Write-Host "===================================================== $pc ====================================================="
                    $testcon=Test-Connection $pc -Quiet
                    if($testcon -eq "True"){
                        foreach($program in $arrayFromFile){
                            Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y $Using:program}
                        }
                    }Else{
                        Write-warning "$pc IS OFFLINE"
                    }
                }
            }
            if($Group -eq 'c'){
                write-host "Service Group"
                foreach($pc in $SERVICE_GROUP_PCS){
                    Write-Host "===================================================== $pc ====================================================="
                    $testcon=Test-Connection $pc -Quiet
                    if($testcon -eq "True"){
                        foreach($program in $arrayFromFile){
                            Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y $Using:program}
                        }
                    }Else{
                        Write-warning "$pc IS OFFLINE"
                    }
                }
            }
            if($Group -eq 'd'){
                write-host "Test Group"
                foreach($pc in $TEST_GROUP_PCS){
                    Write-Host "===================================================== $pc ====================================================="
                    $testcon=Test-Connection $pc -Quiet
                    if($testcon -eq "True"){
                        foreach($program in $arrayFromFile){
                            Invoke-Command -ComputerName $pc -ScriptBlock{choco upgrade -y $Using:program}
                        }
                    }Else{
                        Write-warning "$pc IS OFFLINE"
                    }
                }
            }
        }
    }
}