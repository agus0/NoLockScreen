/*
    Nombre: NoLockScreen.
    Autor: Agustin Padron (code@agus0.com)
    Descripcion: Programa que activa o desactiva la pantalla de bloque en Windows 8,8.1 y 10
                 a partir de la modificacion del registro. Requiere permiso de administrador.
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>

using namespace std;

void lockScreen (bool enable);

int main(int argc, char **argv) {
    string command = (string)argv[1];
    int    estado = 2;
    if (command == "enable") {
        lockScreen(true);
    }else if(command == "disable") {
        lockScreen(false);
    }else{
        cout << "NoLockScreen" << endl;
        while (estado != 0 && estado != 1) {
            cout << endl << "Elija 0 para desactivar la pantalla de bloqueo o 1 para activarla: ";
            cin >> estado;
        }
        if (estado == 0) {
            lockScreen(false);
        }else{
            lockScreen(true);
        }
    }
    return 0;
}

void lockScreen (bool enable) {
    HKEY hKey;
    DWORD value;

    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\Personalization", 0, KEY_ALL_ACCESS, &hKey);
    if (enable) {
        value = 0;
        cout << endl << "LockScreen activado." << endl;
    }else{
        value = 1;
        cout << endl << "LockScreen desactivado." << endl;
    }
    RegSetValueEx(hKey, TEXT("NoLockScreen"), 0, REG_DWORD, (const BYTE*)&value, sizeof(value));
    RegCloseKey(hKey);
}
