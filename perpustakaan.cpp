#include <iostream>
#include <fstream>
#include <string>
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
    bool status; //0 = belum dikembalikan . 1 = sudah dikembalikan
};

bool cekkeaktifan(string id_anggota){
    ifstream file("anggota.txt");
    if (!file.is_open()) {
        cout << "FILE TIDAK DITEMUKAN";
        return false;
    }

    string line;
    while(getline (file, line)) {
        int pss1=0, pss2;
        string data[7];
        for (int i=0; i<7; i++) {
            pss2 = line.find("|", pss1);
            if(pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr(pss1, pss2-pss1);
            pss1 = pss2 + 1;
        }
    
        if(data[0] == id_anggota) {
            file.close();
            return data[6] == "!";
        }
    }
    file.close();
    return false;
}

bool cekstok(string id_buku) {
    ifstream file("buku.txt");
    if (!file.is_open()) {
        cout << "FILE TIDAK DAPAT DIBUKA";
    return false;
}

    string line;
    while (getline(file, line)) {
        int pss1 = 0, pss2;
        string data[7];
        for (int i=0; i<7; i++) {
            pss2 = line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size(); 
            data[i] = line.substr(pss1, pss2-pss1);
            pss1  = pss2 +1;
        }
        if (data[0] == id_buku) {
            int stok = stoi(data[6]);
            file.close();
            return stok > 0;
        }
        }
    file.close();
    return false; 
}

void kurangistok(string id_buku) {
    ifstream file("buku.txt");
    if (!file.is_open()) {
        cout << "gagal";
        return;
    }
    ofstream t("t.txt");
    if (!t.is_open()) {
        cout << "gagal";
        return;
    }
    string line;
    while (getline(file, line)) {
        int pss1 = 0, pss2;
        string data[7];
        for (int i=0; i<7; i++) {
            pss2=line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr (pss1, pss2 - pss1);
            pss1 = pss2 + 1;
        }
        if (data[0]== id_buku) {
            int stok = stoi(data[6]);
            stok++;
            t << data[0] << "|" << data[1] << "|" << data[2] << "|" << data[3] << "|" << data[4] << "|" << data[5] << "|"<< stok << endl;
        }
        else {
            t << line << endl;
        }
    }
file.close();
t.close();
remove("buku.txt");
rename("temp.txt", "buku.txt");
}

 void tambahstok(string id_buku) {};
void tambahpeminjaman();
void tampilpeminjaman();
void caripeminjaman();
void pengembalianbuku();
void hitungdenda();




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