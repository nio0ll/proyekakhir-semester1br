#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

struct TTL {
    string tempat;
    string tanggal;
    string bulan;
    int tgl;
    int bln;
    string tahun;
    string gabung;
};

struct ANGGOTA {
    string id_anggota;
    string kode_anggota;
    string nama;
    string alamat;
    TTL ttl;
    string email;
    int status;
    string sstatus;
};

struct PETUGAS {
    string id_petugas;
    string username;
    string password;
    string nama;
};

struct BUKU {
    string id_buku;
    string isbn;
    string judul;
    string pengarang;
    string penerbit;
    string tahun_terbit;
    string sstok;
    int stok;
};

struct PEMINJAMAN {
    string id_peminjam;
    string id_anggota;
    string id_buku;
    string id_petugas;
    string tanggal_pinjam;
    string tanggal_kembali;
    int denda;
    int status;
};

string kembarkodeanggota() {
    ifstream file("anggota.txt");
    ANGGOTA data;
    int hitung = 0;
    string baris, kode;

    while (getline(file, baris)) {
        stringstream ss(baris);
        getline(ss, kode, '|');
        getline(ss, kode, '|');
        if (kode.size() >= 8 && kode.substr(0, 8) == data.kode_anggota) {
            hitung++;
        }
    }
    file.close();
    int urut = hitung + 1;
    string u = (urut < 10 ? "00" : (urut < 100 ? "0" : "")) + to_string(urut);
    return data.kode_anggota + u;
}

void tambahanggota() {
    ofstream fileOutput("anggota.txt", ios::app);
    ANGGOTA data;
    int makshari, th, n;
    bool kabisat;
    cout << "\nJumlah anggota yang akan ditambah: ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        do {
            cout << "ID Anggota (6 digit)\t: ";
            getline(cin, data.id_anggota);
        } while (data.id_anggota.length() != 6);
        cout << "Nama\t\t\t: ";
        getline(cin, data.nama);
        cout << "Alamat\t\t\t: ";
        getline(cin, data.alamat);
        cout << "Tempat lahir\t\t: ";
        getline(cin, data.ttl.tempat);
        do {
            cout << "Tahun lahir (0000)\t: ";
            getline(cin, data.ttl.tahun);
        } while (data.ttl.tahun.length() != 4);
        do {
            cout << "Bulan lahir (1-12)\t: ";
            cin >> data.ttl.bln;
            cin.ignore();
            data.ttl.bulan = (data.ttl.bln < 10) ? "0" + to_string(data.ttl.bln) : to_string(data.ttl.bln);
        } while (data.ttl.bln < 1 || data.ttl.bln > 12);
        if (data.ttl.bln == 2) {
            th = stoi(data.ttl.tahun);
            kabisat = (th % 4 == 0 && (th % 100 != 0 || th % 400 == 0));
            makshari = kabisat ? 29 : 28;
        } else if (data.ttl.bln == 4 || data.ttl.bln == 6 || data.ttl.bln == 9 || data.ttl.bln == 11) {
            makshari = 30;
        } else {
            makshari = 31;
        }
        do {
            cout << "Tanggal lahir (1-" << makshari << ")\t: ";
            cin >> data.ttl.tgl;
            cin.ignore();
            data.ttl.tanggal = (data.ttl.tgl < 10) ? "0" + to_string(data.ttl.tgl) : to_string(data.ttl.tgl);
        } while (data.ttl.tgl < 1 || data.ttl.tgl > makshari);
        do {
            cout << "Email (Wajib @ dan .com): ";
            getline(cin, data.email);
        } while (data.email.find('@') == string::npos || data.email.find(".com") == string::npos);
        data.status = 1;
        data.kode_anggota = data.ttl.tahun + data.ttl.bulan + data.ttl.tanggal;
        data.kode_anggota += kembarkodeanggota();
        data.ttl.gabung = data.ttl.tempat + " " + data.ttl.tanggal + "-" + data.ttl.bulan + "-" + data.ttl.tahun;
        cout << "Kode Anggota\t\t: " << data.kode_anggota;
        if (fileOutput.is_open()) {
            fileOutput << data.id_anggota << "|" << data.kode_anggota << "|" << data.nama << "|"
                       << data.alamat << "|" << data.ttl.gabung << "|" << data.email << "|" << data.status << endl;
            cout << "\n\nData berhasil dikirim!\n";
        } else {
            cout << "\n\nData gagal dikirim!\n";
        }
    }
    fileOutput.close();
}

void daftaranggota() {
    ifstream fileInput("anggota.txt");
    if (fileInput.is_open()) {
        string line;
        cout << "\nDaftar Anggota:\n\n";
        while (getline(fileInput, line)) {
            cout << line << endl;
        }
        cout << "\nFile berhasil dibuka!\n";
        fileInput.close();
    } else {
        cout << "\nFile gagal dibuka!\n" << endl;
    }
}

void daftaranggotaaktif() {
    ifstream fileInput("anggota.txt");
    if (!fileInput.is_open()) {
        cout << "\nFile gagal dibuka!\n";
        return;
    }
    string line;
    cout << "\nDaftar Anggota Aktif:\n\n";
    while (getline(fileInput, line)) {
        int pos = line.rfind("|");
        if (pos == string::npos) continue;
        string status = line.substr(pos + 1);
        if (status == "1") {
            cout << line << endl;
        }
    }
    cout << "\nFile berhasil dibuka!\n";
    fileInput.close();
}

void carianggota() {
    ifstream fileInput("anggota.txt");
    if (fileInput.is_open()) {
        ANGGOTA cari;
        string cariid, teks;
        bool ketemu = false;
        cout << "\nInput ID anggota yang dicari: ";
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
                cout << "\nData Ditemukan!\n\n";
                cout << "ID Anggota: " << cari.id_anggota << endl;
                cout << "Kode\t  : " << cari.kode_anggota << endl;
                cout << "Nama\t  : " << cari.nama << endl;
                cout << "Alamat\t  : " << cari.alamat << endl;
                cout << "TTL\t  : " << cari.ttl.gabung << endl;
                cout << "Email\t  : " << cari.email << endl;
                cout << "Status\t  : " << cari.sstatus << endl;
                ketemu = true;
                break;
            }
        }
        if (!ketemu) {
            cout << "\nData dengan ID " << cariid << " tidak ditemukan.\n";
        }
        fileInput.close();
        cout << "\nFile berhasil dibuka!\n";
    } else {
        cout << "\nFile gagal dibuka!\n";
    }
}

void hapusanggota() {
    ifstream fileInput("anggota.txt");
    ofstream fileTemp("temp.txt");
    if (fileInput.is_open() && fileTemp.is_open()) {
        ANGGOTA data;
        string teks, hapus;
        bool ketemu = false;
        cout << "\nMasukkan ID anggota yang ingin di-nonaktifkan: ";
        cin >> hapus;

        while (getline(fileInput, teks)) {
            if (teks == "") continue;
            stringstream ss(teks);
            getline(ss, data.id_anggota, '|');
            getline(ss, data.kode_anggota, '|');
            getline(ss, data.nama, '|');
            getline(ss, data.alamat, '|');
            getline(ss, data.ttl.gabung, '|');
            getline(ss, data.email, '|');
            getline(ss, data.sstatus);

            if (data.id_anggota == hapus) {
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

        cout << "\nFile sudah diperbarui!\n";
    } else {
        cout << "\nFile gagal dibuka!\n";
    }
}

void tambahBuku() {
    ofstream file("buku.txt", ios::app);
    int jum;
    cout << "\nMasukkan jumlah buku yang akan ditambahkan: ";
    cin >> jum;
    cin.ignore();
    for (int i = 0; i < jum; i++) {
        BUKU b;

        do {
            cout << "ID Buku (6 digit)\t: ";
            getline(cin, b.id_buku);
        } while (b.id_buku.length() != 6);

        do {
            cout << "Masukkan ISBN (11 karakter): ";
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
        } while (b.tahun_terbit.length() != 4);

        cout << "Stok\t\t\t   : ";
        cin >> b.stok;

        if (file.is_open()) {
            file << b.id_buku << "|"
                 << b.isbn << "|"
                 << b.judul << "|"
                 << b.pengarang << "|"
                 << b.penerbit << "|"
                 << b.tahun_terbit << "|"
                 << b.stok << endl;
           cout << "\nData buku berhasil ditambahkan!\n";
        } else {
            cout << "\nData buku gagal ditambahkan!\n";
        }
    }
    file.close();
}

void tampilBuku() {
    ifstream fileInput("buku.txt");
    if (fileInput.is_open()) {
        string line;
        cout << "\nDaftar Buku:\n\n";
        while (getline(fileInput, line)) {
            cout << line << endl;
        }
        cout << "\nFile berhasil dibuka!\n";
        fileInput.close();
    } else {
        cout << "\nFile gagal dibuka!\n" << endl;
    }
}

void cariBuku() {
    ifstream fileInput("buku.txt");
    if (fileInput.is_open()) {
        BUKU cari;
        string carijudul, teks;
        bool ketemu = false;
        cout << "\nMasukkan judul buku yang dicari: ";
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
                cout << "\nData Ditemukan!\n\n";
                cout << "ID Buku\t\t: " << cari.id_buku << endl;
                cout << "ISBN\t\t: " << cari.isbn << endl;
                cout << "Judul\t\t: " << cari.judul << endl;
                cout << "Pengarang\t: " << cari.pengarang << endl;
                cout << "Penerbit\t: " << cari.penerbit << endl;
                cout << "Tahun terbit\t: " << cari.tahun_terbit << endl;
                cout << "Stok\t\t: " << cari.sstok << endl;
                ketemu = true;
                break;
            }
        }
        if (!ketemu) {
            cout << "\nBuku dengan Judul " << carijudul << " tidak ditemukan.\n";
        }
        fileInput.close();
        cout << "\nFile berhasil dibuka!\n";
    } else {
        cout << "\nFile gagal dibuka!\n";
    }
}

void editBuku() {
    ifstream fileInput("buku.txt");
    ofstream fileTemp("temp.txt");
    string teks, cari;
    bool ketemu = false;

    if (fileInput.is_open() && fileTemp.is_open()) {
        cin.ignore();
        cout << "\nMasukkan judul buku yang ingin diedit: ";
        getline(cin, cari);

        while (getline(fileInput, teks)) {
            stringstream ss(teks);
            BUKU b;

            getline(ss, b.id_buku, '|');
            getline(ss, b.isbn, '|');
            getline(ss, b.judul, '|');
            getline(ss, b.pengarang, '|');
            getline(ss, b.penerbit, '|');
            getline(ss, b.tahun_terbit, '|');
            getline(ss, b.sstok, '|');

            if (b.judul == cari) {
                ketemu = true;

                cout << "\nData Ditemukan!\n\n";
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
                if (newisbn == "") newisbn = b.isbn;

                cout << "Judul baru: ";
                getline(cin, newjudul);
                if (newjudul == "") newjudul = b.judul;

                cout << "Pengarang baru: ";
                getline(cin, newpengarang);
                if (newpengarang == "") newpengarang = b.pengarang;

                cout << "Penerbit baru: ";
                getline(cin, newpenerbit);
                if (newpenerbit == "") newpenerbit = b.penerbit;

                cout << "Tahun terbit baru: ";
                getline(cin, newtahun);
                if (newtahun == "") newtahun = b.tahun_terbit;

                cout << "Stok baru: ";
                getline(cin, newstok);
                int stokBaru;
                if (newstok == "") {
                    stokBaru = b.stok;
                } else {
                    stokBaru = stoi(newstok);
                }

                fileTemp << b.id_buku << "|"
                         << newisbn << "|"
                         << newjudul << "|"
                         << newpengarang << "|"
                         << newpenerbit << "|"
                         << newtahun << "|"
                         << stokBaru << endl;

            } else {
                fileTemp << teks << endl;
            }
        }

        fileInput.close();
        fileTemp.close();

        remove("buku.txt");
        rename("temp.txt", "buku.txt");

        if (!ketemu) {
            cout << "\nData tidak ditemukan.\n";
        } else {
            cout << "\nData buku berhasil diedit!\n";
        }
    }
}

void hapusBuku() {
    ifstream fileInput("buku.txt");
    ofstream fileTemp("h.txt");
    if (fileInput.is_open() && fileTemp.is_open()) {
        BUKU data;
        string teks, hapus;
        bool ketemu = false;
        cout << "\nMasukkan judul buku yang ingin dihapus: ";
        cin.ignore();
        getline(cin, hapus);
        while (getline(fileInput, teks)) {
            if (teks == "") continue;
            stringstream ss(teks);
            getline(ss, data.id_buku, '|');
            getline(ss, data.isbn, '|');
            getline(ss, data.judul, '|');
            getline(ss, data.pengarang, '|');
            getline(ss, data.penerbit, '|');
            getline(ss, data.tahun_terbit, '|');
            getline(ss, data.sstok);

            if (data.judul != hapus) {
                fileTemp << data.id_buku << "|"
                         << data.isbn << "|"
                         << data.judul << "|"
                         << data.pengarang << "|"
                         << data.penerbit << "|"
                         << data.tahun_terbit << "|"
                         << data.sstok << endl;
            } else {
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
        cout << "\nFile sudah diperbarui!\n";
    } else {
        cout << "\nFile gagal dibuka!\n";
    }
}

bool cekkeaktifan(string id_anggota) {
    ifstream file("anggota.txt");
    if (!file.is_open()) {
        cout << "FILE TIDAK DITEMUKAN";
        return false;
    }
    string line;
    while (getline(file, line)) {
        int pss1 = 0, pss2;
        string data[7];
        for (int i = 0; i < 7; i++) {
            pss2 = line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr(pss1, pss2 - pss1);
            pss1 = pss2 + 1;
        }

        if (data[0] == id_anggota) {
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
    while (getline(file, line)) {
        int pss1 = 0, pss2;
        string data[7];
        for (int i = 0; i < 7; i++) {
            pss2 = line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr(pss1, pss2 - pss1);
            pss1 = pss2 + 1;
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
        for (int i = 0; i < 7; i++) {
            pss2 = line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr(pss1, pss2 - pss1);
            pss1 = pss2 + 1;
        }
        if (data[0] == id_buku) {
            int stok = stoi(data[6]);
            stok--;
            t << data[0] << "|" << data[1] << "|" << data[2] << "|" << data[3] << "|" << data[4] << "|" << data[5] << "|" << stok << endl;
        } else {
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
    BUKU buk;
    string line;
    while (getline(file, line)) {
        int pss1 = 0, pss2;
        string data[7];
        for (int i = 0; i < 7; i++) {
            pss2 = line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr(pss1, pss2 - pss1);
            pss1 = pss2 + 1;
        }
        if (data[0] == id_buku) {
            int stok = stoi(data[6]);
            stok++;
            t << data[0] << "|" << data[1] << "|" << data[2] << "|" << data[3] << "|" << data[4] << "|" << data[5] << "|" << stok << endl;
        } else {
            t << line << endl;
        }
    }
    file.close();
    t.close();
    remove("buku.txt");
    rename("t.txt", "buku.txt");
}

string formatTanggal(int d, int m, int y) {
    return to_string(d) + "-" + to_string(m) + "-" + to_string(y);
}

string tambah7hari(string tgl) {
    int d = stoi(tgl.substr(0, 2));
    int m = stoi(tgl.substr(3, 2));
    int y = stoi(tgl.substr(6, 4));
    d += 7;
    int hariBulan[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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

int selisihTanggal(string t1, string t2) {
    int d1 = stoi(t1.substr(0, 2));
    int m1 = stoi(t1.substr(3, 2));
    int y1 = stoi(t1.substr(6, 4));

    int d2 = stoi(t2.substr(0, 2));
    int m2 = stoi(t2.substr(3, 2));
    int y2 = stoi(t2.substr(6, 4));
    int hariBulan[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    auto total = [&](int d, int m, int y) {
        long jum = y * 365 + d;
        for (int i = 1; i < m; i++) jum += hariBulan[i];
        return jum;
    };
    return total(d2, m2, y2) - total(d1, m1, y1);
}

void tambahpeminjaman() {
    PEMINJAMAN p;
    ofstream file("peminjaman.txt", ios::app);
    if (!file.is_open()) {
        cout << "gagal";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "\nID Peminjaman (6 digit) : ";
        getline(cin, p.id_peminjam);
        if (p.id_peminjam.length() != 6) cout << "ID harus 6 digit!\n";
    } while (p.id_peminjam.length() != 6);
    do {
        cout << "\nID Anggota (6 digit)    : ";
        getline(cin, p.id_anggota);
        if (p.id_anggota.length() != 6) cout << "ID harus 6 digit!\n";
    } while (p.id_anggota.length() != 6);
    do {
        cout << "\nID Buku (6 digit)       : ";
        getline(cin, p.id_buku);
        if (p.id_buku.length() != 6) cout << "ID harus 6 digit!\n";
    } while (p.id_buku.length() != 6);
    cout << "ID Petugas : ";
    gdo {
        cout << "\nID Petugas (6 digit)    : ";
        getline(cin, p.id_petugas);
        if (p.id_petugas.length() != 6) cout << "ID harus 6 digit!\n";
    } while (p.id_petugas.length() != 6);

    if (!cekkeaktifan(p.id_anggota)) {
        cout << "\nAggota tidak aktif.\n";
        file.close();
        return;
    }
    if (!cekstok(p.id_buku)) {
        cout << "\nBuku tidak tersedia.\n";
        file.close();
        return;
    }

    cout << "Tanggal Peminjaman (DD-MM-YYYY): ";
    getline(cin, p.tanggal_pinjam);
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
    cout << "\nPeminjaman berhasil ditambahkan!\n";
}

void tampilpeminjaman() {
    ifstream file("peminjaman.txt");
    if (!file.is_open()) {
        cout << "\nGagal.\n";
        return;
    }
    string line;
    cout << "\nData Peminjaman\n";
    while (getline(file, line)) {
        int pss1 = 0, pss2;
        string data[8];
        for (int i = 0; i < 8; i++) {
            pss2 = line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr(pss1, pss2 - pss1);
            pss1 = pss2 + 1;
        }
        cout << "ID Peminjaman : " << data[0] << endl;
        cout << "ID Anggota : " << data[1] << endl;
        cout << "ID Buku : " << data[2] << endl;
        cout << "ID Petugas : " << data[3] << endl;
        cout << "Tanggal Pinjam : " << data[4] << endl;
        cout << "Tanggal Kembali : " << data[5] << endl;
        cout << "Denda : " << data[6] << endl;
        cout << "Status : " << (data[7] == "1" ? "Dipinjam" : "Dikembalikan") << endl;
    }
    file.close();
}

void caripeminjaman() {
    ifstream file("peminjaman.txt");
    if (!file.is_open()) {
        cout << "\nGagal.\n";
        return;
    }

    string cari, line;
    bool ketemu = false;
    cin.ignore();
    cout << "\nID Peminjaman : ";
    getline(cin, cari);
    while (getline(file, line)) {
        int pss = line.find("|");
        string id = line.substr(0, pss);
        if (id == cari) {
            cout << "\nData yang ditemukan : " << line << endl;
            ketemu = true;
            break;
        }
    }
    if (!ketemu) cout << "\nData tidak ditemukan.\n";
    file.close();
}

float hitungdenda(int telat) {
    if (telat > 0) return telat * 1000.0f;
    return 0.0f;
}

void pengembalianbuku() {
    fstream file("peminjaman.txt", ios::in);
    if (!file.is_open()) {
        cout << "\nGagal.\n";
        return;
    }
    ofstream tt("tt.txt");
    if (!tt.is_open()) {
        cout << "\nGagal.\n";
        return;
    }

    string cariID, line;
    bool ketemu = false;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nID Peminjaman yang dikembalikan : ";
    getline(cin, cariID);
    if (cariID.empty()) {
        cout << "\nID Peminjaman tidak ditemukan.\n";
        file.close();
        remove("tt.txt");
        return;
    }

    while (getline(file, line)) {
        int pss1 = 0, pss2;
        string data[8];
        for (int i = 0; i < 8; i++) {
            pss2 = line.find("|", pss1);
            if (pss2 == string::npos) pss2 = line.size();
            data[i] = line.substr(pss1, pss2 - pss1);
            pss1 = pss2 + 1;
        }

        if (data[0] == cariID) {
            ketemu = true;

            string batasKembali = data[5];
            string tglSekarang;

            do {
                cout << "Tanggal hari ini (DD-MM-YYYY): ";
                getline(cin, tglSekarang);
                if (tglSekarang.length() != 10 || tglSekarang[2] != '-' || tglSekarang[5] != '-') {
                    cout << "Format tanggal salah (DD-MM-YYYY)!\n";
                    tglSekarang.clear();
                } else break;
            } while (true);

            int telat = selisihTanggal(batasKembali, tglSekarang);
            if (telat < 0) telat = 0;

            float denda = hitungdenda(telat);

            tt << data[0] << "|" << data[1] << "|" << data[2] << "|" << data[3] << "|" << data[4] << "|" << data[5] << "|" << (int)denda << "|0" << endl;

            tambahstok(data[2]);
            cout << "\nBuku sudah dikembalikan\n";
            cout << "Terlambat: " << telat << " hari\n";
            cout << "Denda : Rp " << (int)denda << "\n";
        } else {
            tt << line << endl;
        }
    }

    file.close();
    tt.close();

    remove("peminjaman.txt");
    rename("tt.txt", "peminjaman.txt");

    if (!ketemu)
        cout << "\nID Peminjaman tidak ditemukan.\n";
}

void tambahPetugas(int n) {
    ofstream file("petugas.txt", ios::app);

    PETUGAS p;

    for (int i = 0; i < n; i++) {
        cout << "\nMasukkan ID Petugas: ";
        getline(cin, p.id_petugas);

        cout << "Masukkan Nama      : ";
        getline(cin, p.nama);

        cout << "Masukkan Username  : ";
        getline(cin, p.username);

        cout << "Masukkan Password  : ";
        getline(cin, p.password);

        file << p.id_petugas << "|"
             << p.username << "|"
             << p.password << "|"
             << p.nama << endl;
    }

    file.close();
    cout << "\nData petugas berhasil ditambahkan!\n";
}

void tampilPetugas() {
    ifstream file("petugas.txt");
    PETUGAS p;
    string baris;
    cout << "\nDaftar Petugas\n";
    while (getline(file, baris)) {
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

bool loginPetugas(string username, string password) {
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

int pilihan, menu, menuanggota, menubuku, menupeminjaman, menupetugas, menudaftaranggota;

void menuperpustakaan() {
    do {
        cout << "\033[1;36m"
             << endl
             << R"====ASCII====(──★ ˙ ̟⪩⪨ Selamat Datang !!)====ASCII===="
             << "\033[0m"
             << "\n1. Buat Akun\n2. Masuk\n0. Keluar\nPilihan: ";
        cin >> pilihan;
        cin.ignore();
        if (pilihan == 1) {
            tambahPetugas(1);
        } else if (pilihan == 2) {
            int pilih;
            string user, pass;
            cout << "\nMasukkan Username : ";
            cin >> user;
            cout << "Masukkan Password : ";
            cin >> pass;
            if (loginPetugas(user, pass)) {
                cout << "\nLogin Berhasil!\n";
                do {
                    cout << "\nMENU BUKUKU\n1. Menu Anggota\n2. Menu Buku\n3. Menu Peminjaman\n4. Menu Petugas\n0. Keluar\nPILIHAN: ";
                    cin >> menu;
                    if (menu == 1) {
                        do {
                            cout << "\nMENU ANGGOTA\n1. Tambah Anggota\n2. Daftar Anggota\n3. Cari Anggota\n4. Hapus Anggota\n0. Keluar Menu Anggota\nPILIHAN: ";
                            cin >> menuanggota;
                            if (menuanggota == 1) {
                                tambahanggota();
                            } else if (menuanggota == 2) {
                                cout << "\n1. Anggota Aktif\n2. Semua Anggota\nPILIHAN: ";
                                cin >> menudaftaranggota;
                                if (menudaftaranggota == 1) daftaranggotaaktif();
                                else if (menudaftaranggota == 2) daftaranggota();
                                else cout << "Pilihan tidak valid.";
                            } else if (menuanggota == 3) carianggota();
                            else if (menuanggota == 4) hapusanggota();
                            else if (menuanggota == 0);
                            else cout << "\nPilihan tidak valid.\n";
                        } while (menuanggota != 0);
                    } else if (menu == 2) {
                        do {
                            cout << "\nMENU BUKU\n1. Tambah Buku\n2. Daftar Buku\n3. Cari Buku\n4. Edit Buku\n5. Hapus Buku\n0. Keluar Menu Buku\nPILIHAN: ";
                            cin >> menubuku;
                            if (menubuku == 1) {
                                tambahBuku();
                            } else if (menubuku == 2) {
                                tampilBuku();
                            } else if (menubuku == 3) {
                                cariBuku();
                            } else if (menubuku == 4) {
                                editBuku();
                            } else if (menubuku == 5) {
                                hapusBuku();
                            } else if (menubuku == 0) {
                            } else {
                                cout << "\nPilihan tidak valid.\n";
                            }
                        } while (menubuku != 0);
                    } else if (menu == 3) {
                        do {
                            cout << "\nMENU PEMINJAMAN\n1. Tambah Peminjamn\n2. Tampil Peminjaman\n3. Cari Peminjaman\n4. Pengembalian Buku\n0. Keluar Menu Peminjaman\nPILIHAN: ";
                            cin >> menupeminjaman;
                            if (menupeminjaman == 1) {
                                tambahpeminjaman();
                            } else if (menupeminjaman == 2) {
                                tampilpeminjaman();
                            } else if (menupeminjaman == 3) {
                                caripeminjaman();
                            } else if (menupeminjaman == 4) {
                                pengembalianbuku();
                            } else if (menupeminjaman == 0) {
                            } else {
                                cout << "\nPilihan tidak valid.\n";
                            }
                        } while (menupeminjaman != 0);
                    } else if (menu == 4) {
                        do {
                            cout << "\nMENU PETUGAS\n1. Tambah Petugas\n2. Tampil Petugas\n0. Keluar Menu Petugas\nPILIHAN: ";
                            cin >> menupetugas;
                            if (menupetugas == 1) {
                                int n;
                                cout << "\nJumlah petugas yang akan ditambah: ";
                                cin >> n;
                                cin.ignore();
                                tambahPetugas(n);
                            } else if (menupetugas == 2) {
                                tampilPetugas();
                            } else if (menupetugas == 0) {
                            } else {
                                cout << "\nPilihan tidak valid.\n";
                            }
                        } while (menupetugas != 0);
                    } else if (menu == 0) {
                    } else {
                        cout << "\nPilihan tidak valid.\n";
                    }
                } while (menu != 0);
            } else
                cout << "\nLogin Gagal!\n";
        } else if (pilihan == 0) cout << "\nTerima kasih telah menggunakan layanan kami!\n\n";
        else cout << "\nPilihan tidak valid.\n";
    } while (pilihan != 0);
}

int main() {
    menuperpustakaan();
    return 0;
}
