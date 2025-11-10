#include <iostream>
#include <fstream>
using namespace std;

int menu;

struct TTL{
    string tempat;
    string tanggal;
    string bulan;
    string tahun;
};
struct ANGGOTA{
    string id_anggota;
    string kode_anggota;
    string nama;
    TTL ttl;
    string email;
    bool status;
};
struct PETUGAS{
    string id_petugas;
    string username;
    string password;
    string nama;
};
struct BUKU{
    string id_buku;
    string isbn;
    string judul;
    string pengarang;
    string penerbit;
    string tahun_terbit;
    int stok;
};
struct PEMINJAMAN{
    string id_peminjam;
    string id_anggota;
    string id_buku;
    string id_petugas;
    string tanggal_pinjam;
    string tanggal_kembali;
    int denda;
    bool status;
};

void menuperpustakaan(){
    do {
        cout << "\nDAFTAR PILIHAN\n1. Menu Anggota\n2. Menu Buku\n3. Menu Peminjaman\n4. Menu Petugas\n5. Keluar Program\nPILIHAN: ";
        cin >> menu;
        switch(menu){
        case 1: //Menu Anggota
            
            break;
        case 2: //Menu Buku
            
            break;
        case 3: //Menu Peminjaman
            
            break;
        case 4: //Menu Petugas
            
            break;
        case 5: //Keluar Program
            
            break;
        
        default:
            cout << "Pilihan tidak valid.";
            break;
        }
    } while (menu!=5);
}
void tambahPetugas () {
    ofstream file("petugas.txt", ios ::app);
    petugas p;
    cin.ignore();
    cout << "Masukkan Nama:";
    getline (cin p.nama);
    cout << "Masukkan Username";
    getline (cin p.username);
    cout << "Masukkan Password";
    getline (cin p.password);
    file << p.username << " " << p.password << " " << p.nama " " << endl;
    file.close();
    cout << "data petugas berhasil ditambahkan!";
}
void tampilPetugas() {
    ifstream file("petugas.txt");
    petugas p;
    cout << "\n=== DAFTAR PETUGAS ===\n";
    while (file >> p.username >> p.password) {
        getline(file, p.nama);
        if (!p.nama.empty() && p.nama[0] == '')p.nama.erase(0, 1);
        cout << "nama: " << p.nama << "username: " << p.username << endl;
        }
        file.close();
}
bool loginPetugas (string username, string password) {
    ifstream file("petugas.txt");
    petugas p;
    while (file << p.username << p.password) {
        getline(file, p.nama);
        if (p.username == username && p.password == password) {
            file.close();
            retrun true;
        }
    }
    file.close();
    return false;
}
int main() {
    int pilih;
    string user, pass;

    do{
        cout << "\n=== MENU PETUGAS ===\n";
        cout << "1. Tambah Petugas\n";
        cout << "2. Tampil Petugas\n";
        cout << "3. Login Petugas\n";
        cout << "keluar\n";
        cin >> pilih;

        if (pilih == 1) tambahPetugas();
        else if (pilih == 2) tampilPetugas();
        else if (pilih == 3) {
            cout << "\nMasukkan Username: "; cin >> user;
            cout << "Masukkan Password: "; cin >> pass;
            if (loginPetugas(user, pass))
            cout << "Login Berhasil Selamat Datang" << user << "!\n";
            else 
            cout << "Login Gagal!\n";
        }
    } while (pilih != 0);
    cout << "Program Selesai.\n"
    return 0;
}

int main (){
    menuperpustakaan();
    return 0;
}