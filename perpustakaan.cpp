#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int makshari, hitung, th, menu, menuanggota, menubuku, menupeminjaman, menupetugas, n, ambilnoanggotaterakhir, noanggotaterbaru;
string baris, kode;
bool kabisat;

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
    string sstatus;
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
    int noanggotaterakhir=0;
    while (getline(fileInput, baris)){
        if (baris.size()>=3&&isdigit(baris[0])){
            ambilnoanggotaterakhir = stoi(baris.substr(0, 3));
            if (ambilnoanggotaterakhir > noanggotaterakhir) noanggotaterakhir = ambilnoanggotaterakhir;
        }
    }
    fileInput.close();
    return noanggotaterakhir;
}
string kembarkodeanggota(ANGGOTA data[], int i){
    ifstream file("anggota.txt");
    hitung = 0;

    while(getline(file, baris)){
        stringstream ss(baris);
        getline(ss, kode, '|');
        getline(ss, kode, '|'); 
        if (kode.size()>=8&&kode.substr(0, 8)==data[i].kode_anggota){
            hitung++;
        }
    }
    file.close();
    int urut = hitung + 1;
    string u = (urut<10?"00":(urut<100?"0":"")) + to_string(urut);
    return data[i].kode_anggota + u;
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
            cout << "Tahun lahir (0000)\t:";
            getline(cin, data[i].ttl.tahun);
        } while(data[i].ttl.tahun.length()!=4);
        do {
            cout << "Bulan lahir (1-12)\t:";
            cin >> data[i].ttl.bln;
            cin.ignore();
            data[i].ttl.bulan=(data[i].ttl.bln < 10)?"0"+to_string(data[i].ttl.bln):to_string(data[i].ttl.bln);
        } while(data[i].ttl.bln<1||data[i].ttl.bln>12);                                  
        if (data[i].ttl.bln==2){
            th = stoi(data[i].ttl.tahun);
            kabisat = (th%4==0&&(th%100!=0||th%400==0));
            makshari = kabisat?29:28;
        }
        else if (data[i].ttl.bln==4||data[i].ttl.bln==6||data[i].ttl.bln==9||data[i].ttl.bln==11){
            makshari = 30;
        }
        else {
            makshari = 31;
        }
        do {
            cout << "Tanggal lahir (1-" << makshari << ")\t:";
            cin  >> data[i].ttl.tgl;
            cin.ignore();
            data[i].ttl.tanggal=(data[i].ttl.tgl < 10)?"0"+to_string(data[i].ttl.tgl):to_string(data[i].ttl.tgl);
        } while(data[i].ttl.tgl<1||data[i].ttl.tgl>makshari);
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
        data[i].kode_anggota = kembarkodeanggota(data, i);
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
void carianggota(){
    ifstream fileInput("anggota.txt");
    if(fileInput.is_open()){
        ANGGOTA cari;
        string cariid, teks;
        bool ketemu = false;
        cout << "Input ID anggota yang dicari: ";
        cin >> cariid;
        while (getline(fileInput, teks)) {
            stringstream ss(teks);
            getline(ss, cari.id_anggota, '|');
            getline(ss, cari.kode_anggota, '|');
            getline(ss, cari.nama, '|');
            getline(ss, cari.alamat, '|');
            getline(ss, cari.ttl.gabung, '|');
            getline(ss, cari.email, '|');
            getline(ss, cari.sstatus);

            if (cari.id_anggota == cariid) {
                cout << "\nData Ditemukan!\n";
                cout << "ID Anggota: " << cari.id_anggota << endl;
                cout << "Kode\t  : "     << cari.kode_anggota << endl;
                cout << "Nama\t  : "     << cari.nama << endl;
                cout << "Alamat\t  : "   << cari.alamat << endl;
                cout << "TTL\t  : "      << cari.ttl.gabung << endl;
                cout << "Email\t  : "    << cari.email << endl;
                cout << "Status\t  : "   << cari.sstatus << endl;
                ketemu = true;
                break;
            }
        }
        if (!ketemu) {
            cout << "\nData dengan ID " << cariid << " tidak ditemukan.\n";
        }
        fileInput.close();
        cout << "File berhasil dibuka!\n";
    } else {
        cout << "File gagal dibuka!\n";
    }
}
void hapusanggota(){
    ifstream fileInput("anggota.txt");
    ofstream fileTemp("temp.txt");
    if (fileInput.is_open() && fileTemp.is_open()){
        ANGGOTA data;
        string teks, hapus;
        bool ketemu = false;
        cout << "Masukkan ID anggota yang ingin dihapus: ";
        cin >> hapus;
        while (getline(fileInput, teks)){
            if (teks == "") continue;
            stringstream ss(teks);
            getline(ss, data.id_anggota, '|');
            getline(ss, data.kode_anggota, '|');
            getline(ss, data.nama, '|');
            getline(ss, data.alamat, '|');
            getline(ss, data.ttl.gabung, '|');
            getline(ss, data.email, '|');
            getline(ss, data.sstatus);

            if (data.id_anggota != hapus){
                fileTemp << data.id_anggota << "|"
                         << data.kode_anggota << "|"
                         << data.nama << "|"
                         << data.alamat << "|"
                         << data.ttl.gabung << "|"
                         << data.email << "|"
                         << data.sstatus << endl;
            }
            else{
                ketemu = true;
                cout << "\nData dengan ID " << hapus << " berhasil dihapus!\n";
            }
        }
        if (!ketemu)
            cout << "\nData dengan ID " << hapus << " tidak ditemukan.\n";
        fileInput.close();
        fileTemp.close();
        remove("anggota.txt");
        rename("temp.txt", "anggota.txt");
        cout << "File sudah diperbarui!\n";
    } else {
        cout << "File gagal dibuka!\n";
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
                    carianggota();
                }
                else if(menuanggota==4){//Hapus Anggota
                    hapusanggota();
                }
                else if(menuanggota==5){//Keluar Menu Anggota
                }
                else{
                    cout << "Pilihan tidak valid.";
                }
            } while (menuanggota!=5);
        }
        else if(menu==2){//Menu Buku
            do {
                cout << "\nMENU BUKU\n1. Tambah Buku\n2. Daftar Buku\n3. Cari Buku\n4. Edit Buku\n5. Hapus Buku\n6. Keluar Menu Buku\nPILIHAN: ";
                cin >> menubuku;
                if(menubuku==1){//Tambah Buku
                    
                }
                else if(menubuku==2){//Daftar Buku
                    
                }
                else if(menubuku==3){//Cari Buku

                }
                else if(menubuku==4){//Edit Buku

                }
                else if(menubuku==5){//Hapus Buku

                }
                else if(menubuku==6){//Keluar Menu Buku
                }
                else{
                    cout << "Pilihan tidak valid.";
                }
            } while (menubuku!=6);
        }
        else if(menu==3){//Menu Peminjaman
            do {
                cout << "\nMENU Peminjaman\n1. Cek Keaktifan\n2. Cek Stok\n3. Kurangi Stok\n4. Tambah Stok\n5. Tambah Peminjamn\n6. Tampil Peminjaman\n7. Cari Peminjaman\n8. Pengembalian Buku\n9. Hitung Denda\n10. Keluar Menu Peminjaman\nPILIHAN: ";
                cin >> menupeminjaman;
                if(menupeminjaman==1){//Cek Keaktifan
                    
                }
                else if(menupeminjaman==2){//Cek Stok
                    
                }
                else if(menupeminjaman==3){//Kurangi Stok

                }
                else if(menupeminjaman==4){//Tambah Stok

                }
                else if(menupeminjaman==5){//Tambah Peminjamn

                }
                else if(menupeminjaman==6){//Tampil Peminjamn

                }
                else if(menupeminjaman==7){//Cari Peminjaman

                }
                else if(menupeminjaman==8){//Pengembalian Buku

                }
                else if(menupeminjaman==9){//Hitung Denda

                }
                else if(menupeminjaman==10){//Keluar Menu Peminjaman
                }
                else{
                    cout << "Pilihan tidak valid.";
                }
            } while (menupeminjaman!=10);
        }
        else if(menu==4){//Menu Petugas
            do {
                cout << "\nMENU Petugas\n1. Tambah Petugas\n2. Tampil Petugas\n3. Login Petugas\n4. Keluar Menu Petugas\nPILIHAN: ";
                cin >> menupetugas;
                if(menupetugas==1){//Tambah Petugas
                    
                }
                else if(menupetugas==2){//Tampil Petugas
                    
                }
                else if(menupetugas==3){//Login Petugas

                }
                else if(menupetugas==10){//Keluar Menu Petugas
                }
                else{
                    cout << "Pilihan tidak valid.";
                }
            } while (menupetugas!=4);
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