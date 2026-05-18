#include <iostream>
using namespace std;

class RekeningBank {
protected:
    string nasabah;
    double saldo;

public:
    RekeningBank(string nama, double saldoAwal)
        : nasabah(nama), saldo(saldoAwal) {}

    virtual void potongAdmin() = 0;

    void tampilInfo() const {
        cout << "Nasabah : " << nasabah << endl;
        cout << "Saldo   : Rp " << saldo << endl;
    }

    virtual ~RekeningBank() {}
};

class RekeningSyariah : public RekeningBank {
public:
    RekeningSyariah(string nama, double saldoAwal)
        : RekeningBank(nama, saldoAwal) {}
    void potongAdmin() override {
        cout << "[Syariah] " << nasabah
             << " - Tidak ada potongan biaya admin." << endl;
    }
};

class RekeningKonvensional : public RekeningBank {
private:
    const double BIAYA_ADMIN = 15000.0;

public:
    RekeningKonvensional(string nama, double saldoAwal)
        : RekeningBank(nama, saldoAwal) {}

    void potongAdmin() override {
        saldo -= BIAYA_ADMIN;
        cout << "[Konvensional] " << nasabah
             << " - Dipotong Rp 15.000. Saldo sekarang: Rp "
             << saldo << endl;
    }
};

class RekeningPremium : public RekeningBank {
private:
    const double BATAS_SALDO = 10000000.0;
    const double BIAYA_ADMIN  =    50000.0;

public:
    RekeningPremium(string nama, double saldoAwal)
        : RekeningBank(nama, saldoAwal) {}

    void potongAdmin() override {
        if (saldo > BATAS_SALDO) {
            cout << "[Premium] " << nasabah
                 << " - Saldo > Rp 10.000.000. Bebas biaya admin." << endl;
        } else {
            saldo -= BIAYA_ADMIN;
            cout << "[Premium] " << nasabah
                 << " - Saldo > Rp 10.000.000. Dipotong Rp 50.000. "
                 << "Saldo sekarang: Rp " << saldo << endl;
        }
    }
};

int main() {
    RekeningBank* rekening[] = {
        new RekeningSyariah      ("Focalor",   5000000.0),
        new RekeningKonvensional ("Nahida",   2500000.0),
        new RekeningPremium      ("Capitano",    15000000.0),
        new RekeningPremium      ("Tartaglia",    8000000.0),
    };

    cout << "=== Proses Biaya Admin Akhir Bulan ===" << endl;
    cout << "Bank Gibran-Jaya" << endl;
    cout << "======================================" << endl;

    int n = sizeof(rekening) / sizeof(rekening[0]);
    for (int i = 0; i < n; i++) {
        rekening[i]->potongAdmin();
    }

    for (int i = 0; i < n; i++) {
        delete rekening[i];
    }

    return 0; 
}