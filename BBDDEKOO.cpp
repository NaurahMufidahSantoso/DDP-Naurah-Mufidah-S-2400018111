#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Struktur Mahasiswa
struct Mahasiswa {
    string nim;
    string nama;
    vector<int> nilai;
    double rataRata;
    string status;
};

vector<Mahasiswa> dataMahasiswa;

// Hitung rata-rata dan status
void hitungRataRata(Mahasiswa &m) {
    int total = 0;
    for (size_t i = 0; i < m.nilai.size(); ++i)
        total += m.nilai[i];
    m.rataRata = m.nilai.empty() ? 0 : (double)total / m.nilai.size();
    m.status = (m.rataRata >= 60) ? "Lulus" : "Tidak Lulus";
}

// Buat sorting pakai fungsi biasa
bool compareRataRata(const Mahasiswa &a, const Mahasiswa &b) {
    return a.rataRata > b.rataRata;
}

// Baca data dari file
void bacaDariFile(const string &filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) { cout << "Gagal membuka file " << filename << "\n"; return; }
    dataMahasiswa.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Mahasiswa m;
        string nilaiStr;
        getline(ss, m.nim, ',');
        getline(ss, m.nama, ',');
        while (getline(ss, nilaiStr, ',')) 
            m.nilai.push_back(atoi(nilaiStr.c_str()));
        hitungRataRata(m);
        dataMahasiswa.push_back(m);
    }
    file.close();
    cout << "Data berhasil dibaca dari " << filename << "\n";
}

// Simpan data ke inputMahasiswa.txt
void simpanKeFile(const string &filename) {
    ofstream file(filename.c_str());
    for (size_t i = 0; i < dataMahasiswa.size(); ++i) {
        file << dataMahasiswa[i].nim << "," << dataMahasiswa[i].nama;
        for (size_t j = 0; j < dataMahasiswa[i].nilai.size(); ++j)
            file << "," << dataMahasiswa[i].nilai[j];
        file << endl;
    }
    file.close();
}

// Simpan hasil akhir ke hasilMahasiswa.txt
void simpanHasilAkhir(const string &filename) {
    ofstream file(filename.c_str());
    for (size_t i = 0; i < dataMahasiswa.size(); ++i) {
        file << "NIM: " << dataMahasiswa[i].nim
             << ", Nama: " << dataMahasiswa[i].nama
             << ", Rata-rata: " << dataMahasiswa[i].rataRata
             << ", Status: " << dataMahasiswa[i].status << endl;
    }
    file.close();
    cout << "Hasil akhir disimpan ke " << filename << "\n";
}

// Tampilkan semua data
void tampilkanData() {
    cout << "==================== Data Mahasiswa ====================\n";
    for (size_t i = 0; i < dataMahasiswa.size(); ++i) {
        cout << "NIM     : " << dataMahasiswa[i].nim << endl;
        cout << "Nama    : " << dataMahasiswa[i].nama << endl;
        cout << "Nilai   : ";
        for (size_t j = 0; j < dataMahasiswa[i].nilai.size(); ++j) {
            cout << dataMahasiswa[i].nilai[j];
            if (j != dataMahasiswa[i].nilai.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "Rata2   : " << dataMahasiswa[i].rataRata << endl;
        cout << "Status  : " << dataMahasiswa[i].status << endl;
        cout << "--------------------------------------------------------\n";
    }
}

// Tambah data
void tambahData() {
    Mahasiswa m;
    int jumlahNilai;
    cout << "Masukkan NIM: "; cin >> m.nim;
    cout << "Masukkan Nama: "; cin.ignore(); getline(cin, m.nama);
    cout << "Masukkan jumlah nilai semester: "; cin >> jumlahNilai;
    cout << "Masukkan nilai: ";
    for (int i = 0; i < jumlahNilai; i++) {
        int n; cin >> n; m.nilai.push_back(n);
    }
    hitungRataRata(m);
    dataMahasiswa.push_back(m);
    cout << "Data berhasil ditambahkan.\n";
}

// Update data
void updateData() {
    string nimCari;
    cout << "Masukkan NIM yang ingin diupdate: "; cin >> nimCari;
    for (size_t i = 0; i < dataMahasiswa.size(); ++i) {
        if (dataMahasiswa[i].nim == nimCari) {
            cout << "Masukkan Nama baru: "; cin.ignore(); getline(cin, dataMahasiswa[i].nama);
            dataMahasiswa[i].nilai.clear();
            int jumlahNilai;
            cout << "Masukkan jumlah nilai baru: "; cin >> jumlahNilai;
            cout << "Masukkan nilai: ";
            for (int j = 0; j < jumlahNilai; j++) {
                int n; cin >> n; dataMahasiswa[i].nilai.push_back(n);
            }
            hitungRataRata(dataMahasiswa[i]);
            cout << "Data berhasil diupdate.\n";
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

// Hapus data
void hapusData() {
    string nimCari;
    cout << "Masukkan NIM yang ingin dihapus: "; cin >> nimCari;
    for (vector<Mahasiswa>::iterator it = dataMahasiswa.begin(); it != dataMahasiswa.end(); ++it) {
        if (it->nim == nimCari) {
            dataMahasiswa.erase(it);
            cout << "Data berhasil dihapus.\n";
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

// Cari data
void cariData() {
    string nimCari;
    cout << "Masukkan NIM yang dicari: "; cin >> nimCari;
    for (size_t i = 0; i < dataMahasiswa.size(); ++i) {
        if (dataMahasiswa[i].nim == nimCari) {
            cout << "Ditemukan! Nama: " << dataMahasiswa[i].nama
                 << ", Rata-rata: " << dataMahasiswa[i].rataRata
                 << ", Status: " << dataMahasiswa[i].status << endl;
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

// Sorting
void urutkanData() {
    sort(dataMahasiswa.begin(), dataMahasiswa.end(), compareRataRata);
    cout << "Data berhasil diurutkan berdasarkan rata-rata.\n";
}

// Menu
void menu() {
    int pilihan;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Baca dari File\n2. Tampilkan Data\n3. Tambah Data\n4. Update Data\n5. Hapus Data\n6. Cari Data\n7. Urutkan Data\n8. Simpan Data Mahasiswa\n9. Simpan Hasil Akhir\n10. Keluar\n";
        cout << "Pilih menu: "; cin >> pilihan;
        switch (pilihan) {
            case 1: bacaDariFile("inputMahasiswa.txt"); break;
            case 2: tampilkanData(); break;
            case 3: tambahData(); break;
            case 4: updateData(); break;
            case 5: hapusData(); break;
            case 6: cariData(); break;
            case 7: urutkanData(); break;
            case 8: simpanKeFile("inputMahasiswa.txt"); break;
            case 9: simpanHasilAkhir("hasilMahasiswa.txt"); break;
            case 10: cout << "Keluar program.\n"; break;
            default: cout << "Pilihan salah.\n";
        }
    } while (pilihan != 10);
}

int main() {
    menu();
    return 0;
}
