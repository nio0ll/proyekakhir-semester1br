#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int menu, menuanggota, menubuku, menupeminjaman, menupetugas, n, noanggotaterakhir=0, ambilnoanggotaterakhir, noanggotaterbaru;
string baris;

struct TTL{
    string tempat;
    string tanggal;
    string bulan;
    int tgl;
    int bln;
    string tahun;
    string gabung;
};
struct ANGGOTA{
    string id_anggota;
    string kode_anggota;
    string nama;
    string alamat;
    TTL ttl;
    string email;
    int status;
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
    int status;
};
int nomoraggotaterakhir(){
    ifstream fileInput("anggota.txt");
    while (getline(fileInput, baris)){
        if (baris.size()>=3&&isdigit(baris[0])){
            ambilnoanggotaterakhir = stoi(baris.substr(0, 3));
            if (ambilnoanggotaterakhir > noanggotaterakhir) noanggotaterakhir = ambilnoanggotaterakhir;
        }
    }
    fileInput.close();
    return noanggotaterakhir;
}
void tambahanggota(ANGGOTA data[]){
    ofstream fileOutput("anggota.txt",ios::app);
    cout << "\nJumlah anggota yang akan ditambah: ";
    cin >> n;
    cin.ignore();
    //Input Nama, Alamat, Ttl, Email, Status
    for(int i=0;i<n;i++){
        cout << "Nama\t\t\t:";
        getline(cin, data[i].nama);
        cout << "Alamat\t\t\t:";
        getline(cin, data[i].alamat);
        cout << "Tempat lahir\t\t:";
        getline(cin, data[i].ttl.tempat);
        do {
            cout << "Tanggal lahir (1-31)\t:";
            cin >> data[i].ttl.tgl;
            cin.ignore();
            data[i].ttl.tanggal=(data[i].ttl.tgl < 10)?"0"+to_string(data[i].ttl.tgl):to_string(data[i].ttl.tgl);
        } while(data[i].ttl.tgl<1&&data[i].ttl.tgl>31);
        do {
            cout << "Bulan lahir (1-12)\t:";
            cin >> data[i].ttl.bln;
            cin.ignore();
            data[i].ttl.bulan=(data[i].ttl.bln < 10)?"0"+to_string(data[i].ttl.bln):to_string(data[i].ttl.bln);
        } while(data[i].ttl.bln<1&&data[i].ttl.bln>12);
        do {
            cout << "Tahun lahir (0000)\t:";
            getline(cin, data[i].ttl.tahun);
        } while(data[i].ttl.tahun.length()!=4);
        do {
            cout << "Email (Wajib @, dan .com):";
            getline(cin, data[i].email);
        } while(data[i].email.find('@')==string::npos||data[i].email.find(".com")==string::npos);
        do {
            cout << "Status (0=Nonaktif, 1=Aktif):";
            cin >> data[i].status;
            cin.ignore();
        } while(data[i].status!=0&&data[i].status!=1);
        //Simpan Id & Kode & Ttl
        noanggotaterbaru = nomoraggotaterakhir() + 1;
        data[i].id_anggota = (noanggotaterbaru<10?"00":(noanggotaterbaru<100?"0":""))+to_string(noanggotaterbaru)+"123";
        data[i].kode_anggota = data[i].ttl.tahun + data[i].ttl.bulan + data[i].ttl.tanggal;
        data[i].ttl.gabung = data[i].ttl.tempat + " " + data[i].ttl.tanggal + "-" + data[i].ttl.bulan + "-" + data[i].ttl.tahun;
        //Simpan ke file
        if (fileOutput.is_open()){
            fileOutput << data[i].id_anggota << "|" << data[i].kode_anggota << "|" << data[i].nama << "|" <<
                          data[i].alamat     << "|" << data[i].ttl.gabung   << "|" << data[i].email<< "|" <<
                          data[i].status     << endl;
            cout<<"Data berhasil dikirim!\n";
        }
        else{
            cout<<"Data gagal dikirim!\n";
        }
    }
    fileOutput.close(); //03-11 krg rapi, revisi 
}
void daftaranggota(){
    ifstream fileInput("anggota.txt");
    if (fileInput.is_open()) {
        string line;
        cout << "\nDaftar Anggota:";
        while (getline(fileInput, line)) {
            cout << line << endl;
        }
        cout << "File berhasil dibuka!\n";
        fileInput.close();
    }
    else {
        cout << "File gagal dibuka!\n" << endl;
    }
}
void menuperpustakaan(){
    do {
        cout << "\nDAFTAR PILIHAN\n1. Menu Anggota\n2. Menu Buku\n3. Menu Peminjaman\n4. Menu Petugas\n5. Keluar Program\nPILIHAN: ";
        cin >> menu;
        if(menu==1){//Menu Anggota
            do {
                cout << "\nMENU ANGGOTA\n1. Tambah Anggota\n2. Daftar Anggota\n3. Cari Anggota\n4. Hapus Anggota\n5. Keluar Menu Anggota\nPILIHAN: ";
                cin >> menuanggota;
                if(menuanggota==1){//Tambah Anggota
                    ANGGOTA data[999];
                    tambahanggota(data);
                }
                else if(menuanggota==2){//Daftar Anggota
                    daftaranggota();
                }
                else if(menuanggota==3){//Cari Anggota

                }
                else if(menuanggota==4){//Hapus Anggota

                }
                else if(menuanggota==5){//Keluar Menu Anggota
                }
                else{
                    cout << "Pilihan tidak valid.";
                }
            } while (menuanggota!=5);
        }
        else if(menu==2){//Menu Buku
            
        }
        else if(menu==3){//Menu Peminjaman
            
        }
        else if(menu==4){//Menu Petugas
            
        }
        else if(menu==5){//Keluar Program
        }
        else{
            cout << "Pilihan tidak valid.";
        }
        } while (menu!=5);
}

int main (){
    menuperpustakaan();
    return 0;
}