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

int main (){
    menuperpustakaan();
    return 0;
}