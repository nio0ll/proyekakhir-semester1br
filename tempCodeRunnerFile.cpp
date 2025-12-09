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