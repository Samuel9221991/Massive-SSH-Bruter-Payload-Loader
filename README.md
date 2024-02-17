# Masive SSH Bruter with Payload loader
This program brute the ssh from a .txt IP addresses list then, execute a configured payload when the machine get bruted. The code is written in C++ and high optimized.

## This bruter can do
> - Brute the SSH from IP addresses list
> - Save the bruted machines credentials into a .txt file
> - Execute a command when some machine from the .txt get bruted.
> - Show via terminal the attemped IPs, total IPs, total attemps and bruted IPs.


## Software requeriments
> - Debian or Red Hat linux based OS.
> - libssh from C++ installed.
> - An IP addresses list with least 128 IPs.
> - A .txt file with a payload (can be a random linux command).


## Hardware requeriments
- ### Minimum
> - 1 vCore with least 1300 single-thread score.
> - 1 GB Ram.
- ### Recommended
> - 2 vCores with least 1600 single-thread score.
> - 2 GB Ram.
- ### Real experience (Only for run the extreme version)
> - 6 vCores with least 3000 single-thread score.
> - 4 GB Ram.


## Installation & Execution (Normal version)
- ### One time commands
> - Debian based OS: `apt install libssh-dev wget`
> - Red Hat based OS: `yum install libssh-devel` ***/*** `dnf install libssh-devel`
> - `wget https://github.com/Samuel9221991/Masive-SSH-Bruter-Payload-Loader/releases/download/v1.0/ssh_bruter`
> - `chmod +x ./ssh_bruter`

- ### Execution commands
> - `./ssh_bruter ips_to_brute.txt payload.txt`


## Installation & Execution (Extreme version)
- ### One time commands
> - Debian based OS: `apt install libssh-dev wget`
> - Red Hat based OS: `yum install libssh-devel` ***/*** `dnf install libssh-devel`
> - `wget https://github.com/Samuel9221991/Masive-SSH-Bruter-Payload-Loader/releases/download/v1.0/ssh_bruter_extreme`
> - `ulimit -n 999999`
> - `chmod +x ./ssh_bruter_extreme`

- ### Execution commands
> - `./ssh_bruter_extreme ips_to_brute.txt payload.txt`


## How compile the sorce code (Normal Version)
- ### One time commands
> - Debian based OS: `apt update -y && apt upgrade -y; apt install -y g++ libssh-dev wget`
> - Red Hat based OS: `sudo yum -y update && sudo yum -y install gcc-c++ libssh-devel` ***/*** `sudo dnf -y update && sudo dnf -y install gcc-c++ libssh-devel`
> - `wget https://raw.githubusercontent.com/Samuel9221991/Masive-SSH-Bruter-Payload-Loader/main/ssh_bruter.cpp`

### Compilation commands
> - `g++ ssh_bruter.cpp -o ssh_bruter -lssh -lpthread`


## How compile the sorce code (Extreme Version)
- ### One time commands
> - Debian based OS: `apt update -y && apt upgrade -y; apt install -y g++ libssh-dev wget`
> - Red Hat based OS: `sudo yum -y update && sudo yum -y install gcc-c++ libssh-devel` ***/*** `sudo dnf -y update && sudo dnf -y install gcc-c++ libssh-devel`
> - `wget https://raw.githubusercontent.com/Samuel9221991/Masive-SSH-Bruter-Payload-Loader/main/ssh_bruter_extreme.cpp`

### Compilation commands
> - `g++ ssh_bruter_extreme.cpp -o ssh_bruter_extreme -lssh -lpthread`



![Captura de pantalla 2024-02-17 175730](https://github.com/Samuel9221991/Masive-SSH-Bruter-Payload-Loader/assets/84253067/1d1f1877-7c72-4bb5-982a-54ead5d1894b)

*Made in Mexico <3*

