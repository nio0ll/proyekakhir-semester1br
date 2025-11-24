void tambahPetugas () {
//     ofstream file("petugas.txt", ios ::app);
//     PETUGAS p;
//     cin.ignore();
//     cout << "Masukkan Nama:";
//     getline (cin p.nama);
//     cout << "Masukkan Username";
//     getline (cin p.username);
//     cout << "Masukkan Password";
//     getline (cin p.password);
//     file << p.username << " " << p.password << " " << p.nama << " " << endl;
//     file.close();
//     cout << "data petugas berhasil ditambahkan!";
// }
// void tampilPetugas() {
//     ifstream file("petugas.txt");
//     PETUGAS p;
//     cout << "\n=== DAFTAR PETUGAS ===\n";
//     while (file >> p.username >> p.password) {
//         getline(file, p.nama);
//         if (!p.nama.empty() && p.nama[0] == '')p.nama.erase(0, 1);
//         cout << "nama: " << p.nama << "username: " << p.username << endl;
//         }
//         file.close();
// }
// bool loginPetugas (string username, string password) {
//     ifstream file("petugas.txt");
//     PETUGAS p;
//     while (file << p.username << p.password) {
//         getline(file, p.nama);
//         if (p.username == username && p.password == password) {
//             file.close();
//             return true;
//         }
//     }
//     file.close();
//     return false;
// }