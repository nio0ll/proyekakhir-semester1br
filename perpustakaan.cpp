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
        string data[6];
        for (int i=0; i<=6; i++) { 
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
        string data[6];
        for (int i=0; i<=6; i++) {
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
        string data[6];
        for (int i=0; i<=6; i++) {
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
rename("t.txt", "buku.txt");
}

 void tambahstok(string id_buku) {
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
    while(getline(file, line)) {
        int pss1 = 0, pss2;
        string data[6];
        for (int i=0; i<=6; i++) {
            pss2 = line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
                data[i] + line.substr(pss1, pss2 - pss1);
                pss1 = pss2+1;
        }
        if (data[0] == id_buku) {
            int stok = stoi(data[0]);
            stok++;
            t << data[0] << "|" << data[1] << "|" << data[2] << "|" << data[3] << "|" << data[4] << "|" << data[5] << "|" << stok << endl;
        }
        else {
            t << line << endl;
        }
    }
    file.close();
    t.close();
    remove("buku.close");
    rename("t.txt", "buku.txt");
 }
void tambahpeminjaman() {
    PEMINJAMAN p;
    ofstream file("peminjaman.txt", ios::app);
    if (!file.is_open()) {
        cout << "gagal";
        return;
    }

    cin.ignore();
    cout << "\nTambah peminjam\n";
    cout << "ID peminjaman (6 digit) : ";
    getline(cin, p.id_peminjam);
    cout << "ID Anggota : ";
    getline(cin, p.id_anggota);
    cout << "ID Buku : ";
    getline(cin, p.id_buku);
    cout << "ID Petugas : ";
    getline(cin, p.id_petugas);

    //cek keaktifan anggota dan stok buku
    if (!cekkeaktifan(p.id_anggota)) {
        cout << "anggoa tidak aktif";
        file.close();
        return;
    }
    if (!cekstok(p.id_buku)) {
        cout << "buku tidak tersedia";
        file.close();
        return;
    }

    cout << "Tanggal pinjam : ";
    getline(cin, p.tanggal_pinjam);
    cout << "Tanggal Pengembalian : ";
    getline(cin, p.tanggal_kembali);

    p.denda = 0;
    p.status = 1;
    file << p.id_peminjam << "|" << p.id_anggota << "|" << p.id_buku << "|" << p.id_petugas << "|" << p.tanggal_pinjam << "|" << p.tanggal_kembali << "|" << p.denda << "|" << p.status << endl; 
    
    file.close();
    kurangistok(p.id_buku);
    cout << "peminjaman berhasil dirtambahkan";
}

void tampilpeminjaman(){
    ifstream file("peminjaman.txt");
    if (!file.is_open()) {
        cout << "gagal";
        return;
    }
    string line;
    cout << "\n Data Peminjaman \n";
    while (getline(file, line)) {
        int pss1=0, pss2;
        string data[7];
        for (int i=0; i<=7; i++) {
            pss2 = line.find("|", pss1);
            if(pss2 == string::npos) pss2=line.size();
            data[i]=line.substr(pss1,pss2-pss1);
            pss1=pss2+1;
        }
        cout << "ID peminjaman : " << data[0] << endl;
        cout << "ID anggota : " << data[1] << endl;
        cout << "ID buku : " << data[2] << endl;
        cout << "ID petugas : " << data[3] << endl;
        cout << "pinjam : " << data[4] << endl;
        cout << "kembali : " << data[5] << endl;
        cout << "denda : " << data[6] << endl;
        cout << "status : " << (data[7] == "!"?"dipinjam":"dikembalikan") << endl;
    }
    file.close();
}

void caripeminjaman() {
    ifstream file("peminjaman.txt");
    if (!file.is_open()) {
        cout << "gagal";
        return;
    }

    string cari, line;
    bool ketemu = false;
    cin.ignore();
    cout << "\n ID peminjaman : "; //id peminjaman yang ingin dicari
    getline(cin, cari);
    while (getline(file, line)) {
        int pss = line.find("|");
        string id=line.substr(0, pss);
        if (id==cari) {
            cout << "\n data yang ditemukan : " << line << endl;
            ketemu = true;
            break;
        }
    }
    if (!ketemu) cout << "\n data tidak ditemukan \n";
    file.close();
}

void pengembalianbuku() {
    fstream file("peminjaman.txt", ios :: in);
    if (!file.is_open()) {
        cout << "gagal";
        return;
    }
    ofstream t("t.txt");
    if (!file.is_open()) {
        cout << "gagal";
        return;
    }

    int hari;
    float denda;
    string cariID, line;
    bool ketemu = false;
    cin.ignore ();
    cout << "ID pemijaman yang dikembalikan : ";
    getline(cin, cariID);

    while (getline(file, line)) {
        int pss=line.find ("|");
        string id=line.substr (0, pss);
        if (id==cariID) {
            ketemu = true;
            cout << "jumlah hari telat : ";
            cin >> hari;
            float denda = hitungdenda(hari);

            int pss7 = line.rfind("|");
            string databaru = line.substr (0, pss7);
            t << databaru << "|" << denda << "|0" << endl;

            int pss1 = 0, pss2;
            string data[8];
            for (int i=0; i<8; i++) {
                pss2 = line.find("|", pss1);
                if (pss2 == string :: npos) pss2 = line.size();
                data[i] = line.substr (pss1, pss2-pss1);
                pss1 = pss2-1;
            }
            tambahstok (data[2]);
            cout << "\n buku sudah dikembalikan" << "\n Denda Rp : " << denda << endl;
        }
        else {
            t << line << endl;
        }
    }
    file.close();
    t.close();
    remove ("peminjaman.txt");
    rename ("t.txt", "peminjaman.txt");

    if (!ketemu) 
        cout << "data tidak ditemukan. \n";
}


float hitungdenda(int telat) {
    if (telat > 7)
    return (telat-7) * 1000;
    else 
    return 0;
}




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