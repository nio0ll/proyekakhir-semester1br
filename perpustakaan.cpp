#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

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
    string sstok;
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
    string baris;
    int ambilnoanggotaterakhir, noanggotaterakhir=0;
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
    int hitung = 0;
    string baris, kode;

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
    int makshari, th, n, noanggotaterbaru;
    bool kabisat;
    cout << "\nJumlah anggota yang akan ditambah: ";
    cin >> n;
    cin.ignore();
    // Input Nama, Alamat, Ttl, Email, Status
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
        data[i].status=1;
        //Simpan Id & Kode & Ttl
        noanggotaterbaru = nomoraggotaterakhir() + 1;
        data[i].id_anggota = (noanggotaterbaru<10?"00":(noanggotaterbaru<100?"0":""))+to_string(noanggotaterbaru)+"123";
        data[i].kode_anggota = data[i].ttl.tahun + data[i].ttl.bulan + data[i].ttl.tanggal;
        data[i].kode_anggota = kembarkodeanggota(data, i);
        data[i].ttl.gabung = data[i].ttl.tempat + " " + data[i].ttl.tanggal + "-" + data[i].ttl.bulan + "-" + data[i].ttl.tahun;
        cout << "ID Anggota\t\t: " << data[i].id_anggota
             << "\nKode Anggota\t\t: " << data[i].kode_anggota;
        //Simpan ke file
        if (fileOutput.is_open()){
            fileOutput << data[i].id_anggota << "|" << data[i].kode_anggota << "|" << data[i].nama << "|" <<
                          data[i].alamat     << "|" << data[i].ttl.gabung   << "|" << data[i].email<< "|" <<
                          data[i].status     << endl;
            cout<<"\nData berhasil dikirim!\n";
        }
        else{
            cout<<"\nData gagal dikirim!\n";
        }
    }
    fileOutput.close(); //03-11 krg rapi, revisi 
}
void daftaranggota(){
    ifstream fileInput("anggota.txt");
    if (fileInput.is_open()) {
        string line;
        cout << "\nDaftar Anggota:\n";
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
void daftaranggotaaktif(){
    ifstream fileInput("anggota.txt");
    if (!fileInput.is_open()) {
        cout << "File gagal dibuka!\n";
        return;
    }
    string line;
    cout << "\nDaftar Anggota Aktif:\n";
    while (getline(fileInput, line)) {
        int pos = line.rfind("|");
        if (pos == string::npos) continue; //jika tdk ada sesuatu yg memnuhi syarat
        string status = line.substr(pos + 1);
        if (status == "1") {
            cout << line << endl;
        }
    }
    cout << "File berhasil dibuka!\n";
    fileInput.close();
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
        cout << "Masukkan ID anggota yang ingin di-nonaktifkan: ";
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

            if (data.id_anggota == hapus){
                ketemu = true;
                data.sstatus = "0";  
                cout << "\nStatus anggota ID " << hapus << " berhasil dihapus!\n";
            }

            fileTemp << data.id_anggota << "|"
                     << data.kode_anggota << "|"
                     << data.nama << "|"
                     << data.alamat << "|"
                     << data.ttl.gabung << "|"
                     << data.email << "|"
                     << data.sstatus << endl;
        }

        if (!ketemu)
            cout << "\nData dengan ID " << hapus << " tidak ditemukan.\n";

        fileInput.close();
        fileTemp.close();
        remove("anggota.txt");
        rename("temp.txt", "anggota.txt");

        cout << "File sudah diperbarui!\n";
    }
    else {
        cout << "File gagal dibuka!\n";
    }
}

BUKU daftar[100];
int jumlah = 0;
int nomorbukuterakhir(){
    ifstream fileInput("buku.txt");
    string baris;
    int ambilnobukuterakhir, nobukuterakhir=0;
    while (getline(fileInput, baris)){
        if (baris.size()>=3&&isdigit(baris[0])){
            ambilnobukuterakhir = stoi(baris.substr(0, 3));
            if (ambilnobukuterakhir > nobukuterakhir) nobukuterakhir = ambilnobukuterakhir;
        }
    }
    fileInput.close();
    return nobukuterakhir;
}
void simpanKeFile(const BUKU &b){
    ofstream file("buku.txt", ios::app);
    if (!file) {
        cout << "File gagal dibuka!\n";
        return;
    }

    file << b.id_buku << "|"
         << b.isbn << "|"
         << b.judul << "|"
         << b.pengarang << "|"
         << b.penerbit << "|"
         << b.tahun_terbit << "|"
         << b.stok << endl;

    file.close();
}
void tambahBuku(){
    int jum, nobukuterbaru;
    cout << "Masukkan jumlah buku yang akan ditambahkan: ";
    cin >> jum;

    for (int i = 0; i < jum; i++) {
        BUKU b;
        cout << "\nData buku ke-" << i + 1 << endl;

        nobukuterbaru = nomorbukuterakhir() + 1;
        b.id_buku = (nobukuterbaru<10?"00":(nobukuterbaru<100?"0":""))+to_string(nobukuterbaru);
        cout << "ID Buku\t\t\t   : " << b.id_buku;

        do {
            cout << "\nMasukkan ISBN (11 karakter): ";
            cin >> b.isbn;
            if (b.isbn.length() != 11)
                cout << "ISBN harus 11 karakter!\n";
        } while (b.isbn.length() != 11);

        cin.ignore();
        cout << "Judul\t\t\t   : ";
        getline(cin, b.judul);

        cout << "Pengarang\t\t   : ";
        getline(cin, b.pengarang);

        cout << "Penerbit\t\t   : ";
        getline(cin, b.penerbit);

        do {
            cout << "Tahun terbit (0000)\t   : ";
            getline(cin, b.tahun_terbit);
        } while(b.tahun_terbit.length()!=4);

        cout << "Stok\t\t\t   : ";
        cin >> b.stok;

        simpanKeFile(b);
        cout << "Data buku berhasil ditambahkan!\n";
    }
}
void tampilBuku(){
    ifstream fileInput("buku.txt");
    if (fileInput.is_open()) {
        string line;
        cout << "\nDaftar Buku:\n";
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
void cariBuku(){
    ifstream fileInput("buku.txt");
    if(fileInput.is_open()){
        BUKU cari;
        string carijudul, teks;
        bool ketemu = false;
        cout << "Input judul buku yang dicari: ";
        cin.ignore();
        getline(cin, carijudul);
        while (getline(fileInput, teks)) {
            stringstream ss(teks);
            getline(ss, cari.id_buku, '|');
            getline(ss, cari.isbn, '|');
            getline(ss, cari.judul, '|');
            getline(ss, cari.pengarang, '|');
            getline(ss, cari.penerbit, '|');
            getline(ss, cari.tahun_terbit, '|');
            getline(ss, cari.sstok);

            if (cari.judul == carijudul) {
                cout << "\nData Ditemukan!\n";
                cout << "ID Buku\t\t: " << cari.id_buku << endl;
                cout << "ISBN\t\t: "     << cari.isbn << endl;
                cout << "Judul\t\t: "     << cari.judul << endl;
                cout << "Pengarang\t: "   << cari.pengarang << endl;
                cout << "Penerbit\t: "      << cari.penerbit << endl;
                cout << "Tahun terbit\t: "    << cari.tahun_terbit << endl;
                cout << "Stok\t\t: "   << cari.sstok << endl;
                ketemu = true;
                break;
            }
        }
        if (!ketemu) {
            cout << "\nBuku dengan Judul " << carijudul << " tidak ditemukan.\n";
        }
        fileInput.close();
        cout << "File berhasil dibuka!\n";
    } else {
        cout << "File gagal dibuka!\n";
    }
}
void editBuku(){
    ifstream fileInput("buku.txt");
    ofstream fileTemp("temp.txt");
    string teks, cari;
    bool ketemu = false;

    if(fileInput.is_open() && fileTemp.is_open()){
        cin.ignore();
        cout << "Masukkan judul buku yang ingin diedit: ";
        getline(cin, cari);

        while(getline(fileInput, teks)){
            stringstream ss(teks);
            BUKU b;

            getline(ss, b.id_buku, '|');
            getline(ss, b.isbn, '|');
            getline(ss, b.judul, '|');
            getline(ss, b.pengarang, '|');
            getline(ss, b.penerbit, '|');
            getline(ss, b.tahun_terbit, '|');
            getline(ss, b.sstok, '|');

            if(b.judul == cari){
                ketemu = true;

                cout << "\nData Ditemukan!\n";
                cout << "ID Buku      : " << b.id_buku << endl;
                cout << "ISBN         : " << b.isbn << endl;
                cout << "Judul        : " << b.judul << endl;
                cout << "Pengarang    : " << b.pengarang << endl;
                cout << "Penerbit     : " << b.penerbit << endl;
                cout << "Tahun Terbit : " << b.tahun_terbit << endl;
                cout << "Stok         : " << b.sstok << endl;

                string newisbn, newjudul, newpengarang, newpenerbit, newtahun, newstok;

                cout << "\nMasukkan data baru (Enter = tidak diubah)\n";

                cout << "ISBN baru: ";
                getline(cin, newisbn);
                if(newisbn == "") newisbn = b.isbn;

                cout << "Judul baru: ";
                getline(cin, newjudul);
                if(newjudul == "") newjudul = b.judul;

                cout << "Pengarang baru: ";
                getline(cin, newpengarang);
                if(newpengarang == "") newpengarang = b.pengarang;

                cout << "Penerbit baru: ";
                getline(cin, newpenerbit);
                if(newpenerbit == "") newpenerbit = b.penerbit;

                cout << "Tahun terbit baru: ";
                getline(cin, newtahun);
                if (newtahun == "") newtahun = b.tahun_terbit;

                cout << "Stok baru: ";
                getline(cin, newstok);
                // REVISI: Konversi stok ke int untuk konsistensi. Asli: if(newstok == "") newstok = b.stok; (tipe data campur). Sekarang cek dan konversi.
                int stokBaru;
                if(newstok == "") {
                    stokBaru = b.stok;  // Tetap int
                } else {
                    stokBaru = stoi(newstok);  // Konversi string ke int
                }

                fileTemp << b.id_buku << "|"
                         << newisbn << "|"
                         << newjudul << "|"
                         << newpengarang << "|"
                         << newpenerbit << "|"
                         << newtahun << "|"
                         << stokBaru << endl;  // Output sebagai int

            } else {
                fileTemp << teks << endl;
            }
        }

        fileInput.close();
        fileTemp.close();

        remove("buku.txt");
        rename("temp.txt", "buku.txt");

        if(!ketemu){
            cout << "\nData tidak ditemukan.\n";
        } else {
            cout << "\nData buku berhasil diedit!\n";
        }
    }
}
void hapusBuku(){
    ifstream fileInput("buku.txt");
    ofstream fileTemp("h.txt");
    if (fileInput.is_open() && fileTemp.is_open()){
        BUKU data;
        string teks, hapus;
        bool ketemu = false;
        cout << "Masukkan judul buku yang ingin dihapus: ";
        cin.ignore();
        getline(cin, hapus);
        while (getline(fileInput, teks)){
            if (teks == "") continue;
            stringstream ss(teks);
            getline(ss, data.id_buku, '|');
            getline(ss, data.isbn, '|');
            getline(ss, data.judul, '|');
            getline(ss, data.pengarang, '|');
            getline(ss, data.penerbit, '|');
            getline(ss, data.tahun_terbit, '|');
            getline(ss, data.sstok);

            if (data.judul != hapus){
                fileTemp << data.id_buku << "|"
                         << data.isbn << "|"
                         << data.judul << "|"
                         << data.pengarang << "|"
                         << data.penerbit << "|"
                         << data.tahun_terbit << "|"
                         << data.sstok << endl;
            }
            else{
                ketemu = true;
                cout << "\nBuku dengan judul " << hapus << " berhasil dihapus!\n";
            }
        }
        if (!ketemu)
            cout << "\nBuku dengan judul " << hapus << " tidak ditemukan.\n";
        fileInput.close();
        fileTemp.close();
        remove("buku.txt");
        rename("h.txt", "buku.txt");
        cout << "File sudah diperbarui!\n";
    } else {
        cout << "File gagal dibuka!\n";
    }
}

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
        for (int i=0; i<7; i++) {               // <-- ubah 8 -> 7
            pss2 = line.find("|", pss1);
            if(pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr(pss1, pss2-pss1);
            pss1 = pss2 + 1;
        }
    
        if(data[0] == id_anggota) {
            file.close();
            return data[6] == "1";
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
    BUKU buk;
    string line;
    while (getline(file, line)){
        int pss1 = 0, pss2;
        string data[7];
        for (int i=0; i<7; i++) {
            pss2 = line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size(); 
            data[i] = line.substr(pss1, pss2-pss1);
            pss1  = pss2 +1;
        }
        // REVISI: Bandingkan dengan id_buku (parameter). Asli: if (data[0] == buk.id_buku); (buk.id_buku kosong, selalu false).
        if (data[0] == id_buku) {
            int stok = stoi(data[6]);
            file.close();
            return stok > 0;
        }
        }
    file.close();
    return false; 
}
void kurangistok(string id_buku){
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
        string data[7];               // <-- gunakan 7 field
        for (int i=0; i<7; i++) {     // <-- loop sampai 7
            pss2=line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr (pss1, pss2 - pss1);
            pss1 = pss2 + 1;
        }
        if (data[0]== id_buku) {
            int stok = stoi(data[6]);
            stok--;
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
void tambahstok(string id_buku){
    ifstream file("buku.txt");
    if (!file.is_open()) {
        cout << "gagal";
        return;
    }
    ofstream t("t.txt");
    if (!t.is_open()) {  // REVISI: Cek t.is_open(), bukan file.is_open(). Asli: if (!file.is_open()) { ... } (salah, menyebabkan file t tidak dicek).
        cout << "gagal";
        return;
    }
    BUKU buk;
    string line;
    while(getline(file, line)) {
        int pss1 = 0, pss2;
        string data[7];  // REVISI: Ubah ke [7] untuk konsistensi (7 field: id, isbn, judul, pengarang, penerbit, tahun, stok).
        for (int i=0; i<7; i++) {  // REVISI: Loop hingga 7 untuk hindari out of bounds.
            pss2 = line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
            // REVISI: Assign dengan =, bukan +. Asli: data[i] + line.substr... (salah, tidak assign, menyebabkan data kosong).
            data[i] = line.substr(pss1, pss2 - pss1);
            pss1 = pss2+1;
        }
        // REVISI: Bandingkan dengan id_buku. Asli: if (data[0] == buk.id_buku); (buk.id_buku kosong).
        if (data[0] == id_buku) {
            int stok = stoi(data[6]);
            stok++;  // Tambah stok untuk pengembalian
            t << data[0] << "|" << data[1] << "|" << data[2] << "|" << data[3] << "|" << data[4] << "|" << data[5] << "|" << stok << endl;
        }
        else {
            t << line << endl;
        }
    }
    file.close();
    t.close();
    // REVISI: Nama file benar. Asli: remove("buku.close"); (salah, harus "buku.txt").
    remove("buku.txt");
    rename("t.txt", "buku.txt");
}
string formatTanggal(int d, int m, int y){
    return to_string(d) + "-" + to_string(m) + "-" + to_string(y);
}
string tambah7hari(string tgl){
    int d = stoi(tgl.substr(0,2));
    int m = stoi(tgl.substr(3,2));
    int y = stoi(tgl.substr(6,4));
    d += 7;
    int hariBulan[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (d > hariBulan[m]) {
        d -= hariBulan[m];
        m++;
        if (m > 12) {
            m = 1;
            y++;
        }
    }
    string dd = (d < 10 ? "0" : "") + to_string(d);
    string mm = (m < 10 ? "0" : "") + to_string(m);
    string yy = to_string(y);
    return dd + "-" + mm + "-" + yy;
}
int selisihTanggal(string t1, string t2){
    int d1 = stoi(t1.substr(0, 2));
    int m1 = stoi(t1.substr(3, 2));
    int y1 = stoi(t1.substr(6, 4));

    int d2 = stoi(t2.substr(0, 2));
    int m2 = stoi(t2.substr(3, 2));
    int y2 = stoi(t2.substr(6, 4));
    int hariBulan[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    auto total = [&](int d, int m, int y){
        long jum = y * 365 + d;
        for (int i=1; i<m; i++) jum += hariBulan[i];
        return jum;
    };
    return total(d2,m2,y2) - total(d1,m1,y1);
}
void tambahpeminjaman(){
    PEMINJAMAN p;
    ofstream file("peminjaman.txt", ios::app);
    if (!file.is_open()) {
        cout << "gagal";
        return;
    }

    // Clear input buffer safely (penting setelah `cin >>` di menu)
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nTambah peminjam\n";
    do {
        cout << "ID peminjaman (6 digit) : ";
        getline(cin, p.id_peminjam);
        if (p.id_peminjam.length() != 6) cout << "ID harus 6 digit!\n";  // REVISI: Tambah validasi panjang ID.
    } while (p.id_peminjam.length() != 6);
    cout << "ID Anggota : ";
    getline(cin, p.id_anggota);
    cout << "ID Buku : ";
    getline(cin, p.id_buku);
    cout << "ID Petugas : ";
    getline(cin, p.id_petugas);

    //cek keaktifan anggota dan stok buku
    if (!cekkeaktifan(p.id_anggota)) {
        cout << "anggota tidak aktif";
        file.close();
        return;
    }
    if (!cekstok(p.id_buku)) {
        cout << "buku tidak tersedia";
        file.close();
        return;
    }

    cout << "Tanggal pinjam (DD-MM-YYYY): ";
    getline(cin, p.tanggal_pinjam);
    // REVISI: Tambah validasi format tanggal sederhana untuk hindari crash di stoi().
    if (p.tanggal_pinjam.length() != 10 || p.tanggal_pinjam[2] != '-' || p.tanggal_pinjam[5] != '-') {
        cout << "Format tanggal salah (DD-MM-YYYY)!\n";
        file.close();
        return;
    }
    p.tanggal_kembali = tambah7hari(p.tanggal_pinjam);
    p.denda = 0;
    p.status = 1;
    file << p.id_peminjam << "|" << p.id_anggota << "|" << p.id_buku << "|" << p.id_petugas << "|" << p.tanggal_pinjam << "|" << p.tanggal_kembali << "|" << p.denda << "|" << p.status << endl; 
    
    file.close();
    kurangistok(p.id_buku);
    cout << "peminjaman berhasil ditambahkan";
}
void tampilpeminjaman(){
    ifstream file("peminjaman.txt");
    if (!file.is_open()) {
        cout << "gagal";
        return;  
    }
    string line;
    cout << "\nData Peminjaman \n";
    while (getline(file, line)) {
        int pss1=0, pss2;
        string data[8];  // REVISI: Ubah ke [8] untuk 8 field (id_peminjam, id_anggota, id_buku, id_petugas, tanggal_pinjam, tanggal_kembali, denda, status).
        for (int i=0; i<8; i++) {  // REVISI: Loop hingga 8 untuk hindari out of bounds.
            pss2 = line.find("|", pss1);
            if(pss2 == string::npos) pss2=line.size();
            data[i]=line.substr(pss1,pss2-pss1);
            pss1 = pss2 + 1;
        }
        cout << "ID peminjaman : " << data[0] << endl;
        cout << "ID anggota : " << data[1] << endl;
        cout << "ID buku : " << data[2] << endl;
        cout << "ID petugas : " << data[3] << endl;
        cout << "pinjam : " << data[4] << endl;
        cout << "kembali : " << data[5] << endl;
        cout << "denda : " << data[6] << endl;
        // REVISI: Cek status dengan "1" (dipinjam) atau "0" (dikembalikan). Asli: (data[7] == "!"?"dipinjam":"dikembalikan") (salah, selalu "dipinjam").
        cout << "status : " << (data[7] == "1" ? "dipinjam" : "dikembalikan") << endl;
    }
    file.close();
}
void caripeminjaman(){
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
float hitungdenda(int telat){
    if (telat > 7)
    return (telat-7) * 1000;
    else 
    return 0;
}
void pengembalianbuku(){
    fstream file("peminjaman.txt", ios :: in);
    if (!file.is_open()) {
        cout << "gagal";
        return;
    }
    ofstream t("t.txt");
    if (!t.is_open()) {  // REVISI: Cek t.is_open(). Asli: if (!file.is_open()) { ... } (salah, menyebabkan file t tidak dicek).
        cout << "gagal";
        return;
    }

    string cariID, line;
    bool ketemu = false;
    // REVISI: Hapus cin.ignore() jika tidak perlu, atau pindah ke akhir. Asli: cin.ignore(); (bisa menyebabkan skip input).
    cout << "ID peminjaman yang dikembalikan : ";
    getline(cin, cariID);

    while (getline(file, line)) {
        int pss1 = 0, pss2;
        string data[8];  // REVISI: Ubah ke [8] untuk 8 field.
        for (int i=0; i<8; i++) {  // REVISI: Loop hingga 8 untuk hindari out of bounds.
            pss2 = line.find ("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr(pss1, pss2 - pss1);
            pss1 = pss2 + 1;
        }
       // jika ketemu ID yang ingin dikembalikan
        if (data[0] == cariID) {
            ketemu = true;

            string tanggalPinjam = data[4];
            string batasKembali = data[5];   // tanggal kembali (auto + 7 hari)
            
            string tglSekarang;
            cout << "Tanggal hari ini (DD-MM-YYYY): ";
            getline(cin, tglSekarang);
            // REVISI: Tambah validasi format tanggal.
            if (tglSekarang.length() != 10 || tglSekarang[2] != '-' || tglSekarang[5] != '-') {
                cout << "Format tanggal salah (DD-MM-YYYY)!\n";
                continue;  // Lewatkan jika salah
            }
            int telat = selisihTanggal(batasKembali, tglSekarang);
            if (telat < 0) telat = 0;

            float denda = hitungdenda(telat);
            t << data[0] << "|" << data[1] << "|" << data[2] << "|" << data[3] << "|" << data[4] << "|" << data[5] << "|" << denda << "|0" << endl;

            tambahstok(data[2]);
            cout << "\nBuku sudah dikembalikan\n";
            cout << "Terlambat: " << telat << " hari\n";
            cout << "Denda: Rp " << denda << "\n";
        }
        else {
            t << line << endl;
        }
    }

    file.close();
    t.close();

    remove("peminjaman.txt");
    rename("t.txt", "peminjaman.txt");

    if (!ketemu)
        cout << "ID peminjaman tidak ditemukan.\n";
}

void tambahPetugas(){
    ofstream file("petugas.txt", ios::app);

    int n;
    cout << "\nJumlah petugas yang akan ditambah: ";
    cin >> n;
    cin.ignore();

    PETUGAS p;

    for (int i = 0; i < n; i++) {
        cout << "Masukkan ID Petugas    | ";
        getline(cin, p.id_petugas);

        cout << "Masukkan Nama          | ";
        getline(cin, p.nama);

        cout << "Masukkan Username      | ";
        getline(cin, p.username);

        cout << "Masukkan Password      | ";
        getline(cin, p.password);

        file << p.id_petugas << "|"
             << p.username << "|"
             << p.password << "|"
             << p.nama << endl;
    }

    file.close();
    cout << "Data petugas berhasil ditambahkan!\n";
}
void tampilPetugas(){
    ifstream file("petugas.txt");
    PETUGAS p;
    string baris;
    cout << "\nDaftar Petugas\n";
    while (getline(file, baris)){
        stringstream ss(baris);
        getline(ss, p.id_petugas, '|');
        getline(ss, p.username, '|');
        getline(ss, p.password, '|');
        getline(ss, p.nama);
        if (!p.nama.empty() && p.nama[0] == ' ') p.nama.erase(0, 1);

        cout << "ID Petugas : " << p.id_petugas << endl;
        cout << "Nama       : " << p.nama << endl;
        cout << "Username   : " << p.username << endl;
    }

    file.close();
}
bool loginPetugas(string username, string password){
    ifstream file("petugas.txt");
    PETUGAS p;
    string baris;
    while (getline(file, baris)) {
        stringstream ss(baris);
        getline(ss, p.id_petugas, '|');
        getline(ss, p.username, '|');
        getline(ss, p.password, '|');
        getline(ss, p.nama);
        if (!p.nama.empty() && p.nama[0] == ' ')
            p.nama.erase(0, 1);

        if (p.username == username && p.password == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

int menu, menuanggota, menubuku, menupeminjaman, menupetugas, menudaftaranggota;
void menuperpustakaan(){
    do {
        cout << "\033[1;36m"
           << R"====ASCII====(──★ ˙ ̟⪩⪨ Daftar Pilihan Bukuku !!)====ASCII====" 
           << "\033[0m"
           << "\n1. Menu Anggota\n2. Menu Buku\n3. Menu Peminjaman\n4. Menu Petugas\n0. Keluar Program\nPILIHAN: ";
        cin >> menu;
        if(menu==1){//Menu Anggota
            do {
                cout << "\nMENU ANGGOTA\n1. Tambah Anggota\n2. Daftar Anggota\n3. Cari Anggota\n4. Hapus Anggota\n0. Keluar Menu Anggota\nPILIHAN: ";
                cin >> menuanggota;
                if(menuanggota==1){//Tambah Anggota
                    ANGGOTA data[999];
                    tambahanggota(data);
                }
                else if(menuanggota==2){//Daftar Anggota
                    cout << "\n1. Anggota Aktif\n2. Semua Anggota\nPILIHAN: ";
                    cin >> menudaftaranggota;
                    if(menudaftaranggota==1)daftaranggotaaktif();
                    else if(menudaftaranggota==2)daftaranggota();
                    else cout << "Pilihan tidak valid.";
                }
                else if(menuanggota==3){//Cari Anggota
                    carianggota();
                }
                else if(menuanggota==4){//Hapus Anggota
                    hapusanggota();
                }
                else if(menuanggota==0){//Keluar Menu Anggota
                }
                else{
                    cout << "Pilihan tidak valid.";
                }
            } while (menuanggota!=0);
        }
        else if(menu==2){//Menu Buku
            do {
                cout << "\nMENU BUKU\n1. Tambah Buku\n2. Daftar Buku\n3. Cari Buku\n4. Edit Buku\n5. Hapus Buku\n0. Keluar Menu Buku\nPILIHAN: ";
                cin >> menubuku;
                if(menubuku==1){//Tambah Buku
                    tambahBuku();
                }
                else if(menubuku==2){//Daftar Buku
                    tampilBuku();
                }
                else if(menubuku==3){//Cari Buku
                    cariBuku();
                }
                else if(menubuku==4){//Edit Buku
                    editBuku();
                }
                else if(menubuku==5){//Hapus Buku
                    hapusBuku();
                }
                else if(menubuku==0){//Keluar Menu Buku
                }
                else{
                    cout << "Pilihan tidak valid.";
                }
            } while (menubuku!=0);
        }
        else if(menu==3){//Menu Peminjaman
            do {
                cout << "\nMENU Peminjaman\n1. Cek Keaktifan\n2. Cek Stok\n3. Kurangi Stok\n4. Tambah Stok\n5. Tambah Peminjamn\n6. Tampil Peminjaman\n7. Cari Peminjaman\n8. Pengembalian Buku\n9. Hitung Denda\n0. Keluar Menu Peminjaman\nPILIHAN: ";
                cin >> menupeminjaman;
                string id_anggota, id_buku;
                int telat;
                if(menupeminjaman==1){//Cek Keaktifan
                    cekkeaktifan(id_anggota);
                }
                else if(menupeminjaman==2){//Cek Stok
                    cekstok(id_buku);
                }
                else if(menupeminjaman==3){//Kurangi Stok
                    kurangistok(id_buku);
                }
                else if(menupeminjaman==4){//Tambah Stok
                    tambahstok(id_buku);
                }
                else if(menupeminjaman==5){//Tambah Peminjamn
                    tambahpeminjaman();
                }
                else if(menupeminjaman==6){//Tampil Peminjamn
                    tampilpeminjaman();
                }
                else if(menupeminjaman==7){//Cari Peminjaman
                    caripeminjaman();
                }
                else if(menupeminjaman==8){//Pengembalian Buku
                    pengembalianbuku();
                }
                else if(menupeminjaman==9){//Hitung Denda
                    hitungdenda(telat);
                }
                else if(menupeminjaman==0){//Keluar Menu Peminjaman
                }
                else{
                    cout << "Pilihan tidak valid.";
                }
            } while (menupeminjaman!=0);
        }
        else if(menu==4){//Menu Petugas
            do {
                cout << "\nMENU Petugas\n1. Tambah Petugas\n2. Tampil Petugas\n3. Login Petugas\n0. Keluar Menu Petugas\nPILIHAN: ";
                cin >> menupetugas;
                if(menupetugas==1){//Tambah Petugas
                    tambahPetugas();
                }
                else if(menupetugas==2){//Tampil Petugas
                    tampilPetugas();
                }
                else if(menupetugas==3){//Login Petugas
                   int pilih;
                   string user, pass;
                   cout << "\nMasukkan Username : ";
                   cin >> user;
                   cout << "Masukkan Password : ";
                   cin >> pass;
                   if (loginPetugas(user, pass)) cout << "Login Berhasil!\n";
                   else cout << "Login Gagal!\n";
                }
                else if(menupetugas==0){//Keluar Menu Petugas
                }
                else{
                    cout << "Pilihan tidak valid.";
                }
            } while (menupetugas!=0);
        }
        else if(menu==0){//Keluar Program
        }
        else{
            cout << "Pilihan tidak valid.";
        }
        } while (menu!=0);
}

int main (){
menuperpustakaan();

    return 0;
}
