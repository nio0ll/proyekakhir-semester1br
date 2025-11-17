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

BUKU daftarBuku [100];
int jumlahBuku = 0;

void tambahBuku(){
    fstream file ("buku.txt");
    cout << "\n=== Tambah Buku ===\n";
    cin.ignore();

    cout << "ID Buku        : ";
    getline(cin, daftarBuku[jumlahBuku].id_buku);

    cout << "ISBN           : ";
    getline(cin, daftarBuku[jumlahBuku].isbn);

    cout << "Judul          : ";
    getline(cin, daftarBuku[jumlahBuku].judul);

    cout << "Pengarang      : ";
    getline(cin, daftarBuku[jumlahBuku].pengarang);

    cout << "Penerbit       : ";
    getline(cin, daftarBuku[jumlahBuku].penerbit);

    cout << "Tahun Terbit   : ";
    getline(cin, daftarBuku[jumlahBuku].tahun_terbit);

    cout << "Stok           : ";
    cin >> daftarBuku[jumlahBuku].stok;

    jumlahBuku++;
    cout << "Buku berhasil ditambahkan!\n";
}


void tampilBuku(){
    fstream file ("buku.txt");
    if(jumlahBuku == 0){
        cout << "Belum ada data buku.\n";
        return;
    }
    
    for(int i = 0; i < jumlahBuku - 1; i++){
        for(int j = i+1; j < jumlahBuku; j++){
            if(daftarBuku[i].judul > daftarBuku[j].judul){
                swap(daftarBuku[i], daftarBuku[j]);
            }
        }
    }

    cout << "\n=== DAFTAR BUKU ===\n";
    for(int i = 0; i < jumlahBuku; i++){
        cout << "\nData ke-" << i+1 << endl;
        cout << "ID Buku: " << daftarBuku[i].id_buku << endl;
        cout << "ISBN: " << daftarBuku[i].isbn << endl;
        cout << "Judul: " << daftarBuku[i].judul << endl;
        cout << "Pengarang: " << daftarBuku[i].pengarang << endl;
        cout << "Penerbit: " << daftarBuku[i].penerbit << endl;
        cout << "Tahun Terbit: " << daftarBuku[i].tahun_terbit << endl;
        cout << "Stok: " << daftarBuku[i].stok << endl;
    }
}

void cariBuku(){
    fstream file ("buku.txt");
    cin.ignore();
    string judul;
    cout << "\nMasukkan judul buku: ";
    getline(cin, judul);

    for(int i = 0; i < jumlahBuku; i++){
        if(daftarBuku[i].judul == judul){
            cout << "\n=== Buku Ditemukan ===\n";
            cout << "ID Buku: " << daftarBuku[i].id_buku << endl;
            cout << "ISBN: " << daftarBuku[i].isbn << endl;
            cout << "Judul: " << daftarBuku[i].judul << endl;
            cout << "Pengarang: " << daftarBuku[i].pengarang << endl;
            cout << "Penerbit: " << daftarBuku[i].penerbit << endl;
            cout << "Tahun Terbit: " << daftarBuku[i].tahun_terbit << endl;
            cout << "Stok: " << daftarBuku[i].stok << endl;
            return;
        }
    }

    cout << "Buku tidak ditemukan!\n";
}

void editBuku(){
    fstream file ("buku.txt");
    cin.ignore();
    string id;
    cout << "\nMasukkan ID buku yang mau dicari: ";
    getline(cin, id);

    for(int i = 0; i < jumlahBuku; i++){
        if(daftarBuku[i].id_buku == id){
            cout << "\n=== edit Buku ===\n";

            cout << "Judul baru: ";
            getline(cin, daftarBuku[i].judul);

            cout << "Pengarang baru: ";
            getline(cin, daftarBuku[i].pengarang);

            cout << "Penerbit baru: ";
            getline(cin, daftarBuku[i].penerbit);

            cout << "Tahun Terbit baru : ";
            getline(cin, daftarBuku[i].tahun_terbit);

            cout << "Stok baru: ";
            cin >> daftarBuku[i].stok;

            cout << "Data buku berhasil diperbarui!\n";
            return;
        }
    }

    cout << "ID buku tidak ditemukan.\n";
}

void hapusBuku(){
    fstream file ("buku.txt");
    cin.ignore();
    string id;
    cout << "\nMasukkan ID buku yang mau dihapus: ";
    getline(cin, id);

    for(int i = 0; i < jumlahBuku; i++){
        if(daftarBuku[i].id_buku == id){

            for(int j = i; j < jumlahBuku - 1; j++){
                daftarBuku[j] = daftarBuku[j+1];
            }

            jumlahBuku--;
            cout << "Buku berhasil dihapus!\n";
            return;
        }
    }

    cout << "ID buku tidak ditemukan.\n";
}

    
int main (){
    return 0;
}
