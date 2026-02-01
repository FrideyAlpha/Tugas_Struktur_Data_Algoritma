#include <iostream>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

// ===================================================
// STRUCT DATA BARANG
// Digunakan untuk menyimpan data lengkap setiap barang
// ===================================================
struct Barang {
    int kode;        // Kode unik barang
    string nama;     // Nama barang (boleh mengandung spasi)
    int stok;        // Jumlah stok
    int harga;       // Harga barang
};

// ===================================================
// ARRAY DATA BARANG
// ===================================================
Barang barang[100];
int jumlahBarang = 0;

// ===================================================
// STACK TRANSAKSI (LIFO)
// Menyimpan riwayat transaksi pembelian
// ===================================================
string stackTransaksi[100];
int top = -1;

// ===================================================
// QUEUE PEMBELIAN (FIFO)
// Menyimpan antrian pembelian
// ===================================================
string queuePembelian[100];
int front = 0;
int rear = -1;

// ===================================================
// VARIABEL PENDUKUNG
// ===================================================
int stokMinimum = 5;
int totalPenjualan = 0;

// ===================================================
// FUNGSI MEMBERSIHKAN BUFFER INPUT
// ===================================================
void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ===================================================
// FUNGSI NORMALISASI STRING (LOWERCASE)
// ===================================================
string toLowerCase(string teks) {
    for (char &c : teks) {
        c = tolower(c);
    }
    return teks;
}

// ===================================================
// FUNGSI TRIM SPASI AWAL & AKHIR
// ===================================================
string trim(string teks) {
    while (!teks.empty() && teks.front() == ' ')
        teks.erase(teks.begin());
    while (!teks.empty() && teks.back() == ' ')
        teks.pop_back();
    return teks;
}

// ===================================================
// FUNGSI MENAMPILKAN MENU
// ===================================================
void tampilMenu() {
    cout << "\n=== TOKOKU INVENTORY MANAGER ===\n";
    cout << "1. Tambah Barang\n";
    cout << "2. Lihat Semua Barang\n";
    cout << "3. Cari Barang (Kode / Nama)\n";
    cout << "4. Transaksi Pembelian\n";
    cout << "5. Riwayat Transaksi (Stack)\n";
    cout << "6. Proses Antrian Pembelian (Queue)\n";
    cout << "7. Cek Stok Menipis\n";
    cout << "8. Laporan Penjualan\n";
    cout << "0. Keluar\n";
    cout << "Pilih menu: ";
}

// ===================================================
// PROGRAM UTAMA
// ===================================================
int main() {
    int pilihan;

    do {
        tampilMenu();
        cin >> pilihan;
        clearInput(); // pastikan buffer bersih

        switch (pilihan) {

        // ===============================
        case 1: { // Tambah Barang
            if (jumlahBarang >= 100) {
                cout << "Kapasitas barang penuh.\n";
                break;
            }

            cout << "Kode Barang  : ";
            cin >> barang[jumlahBarang].kode;
            clearInput();

            cout << "Nama Barang  : ";
            getline(cin, barang[jumlahBarang].nama); // AMAN SPASI

            cout << "Stok         : ";
            cin >> barang[jumlahBarang].stok;

            cout << "Harga        : ";
            cin >> barang[jumlahBarang].harga;
            clearInput();

            jumlahBarang++;
            cout << "Barang berhasil ditambahkan.\n";
            break;
        }

        // ===============================
        case 2: { // Lihat Semua Barang
            if (jumlahBarang == 0) {
                cout << "Data barang kosong.\n";
            } else {
                for (int i = 0; i < jumlahBarang; i++) {
                    cout << barang[i].kode << " | "
                         << barang[i].nama << " | "
                         << barang[i].stok << " | "
                         << barang[i].harga << endl;
                }
            }
            break;
        }

        // ===============================
        case 3: { // Cari Barang (Kode / Nama)
            string input;
            bool ditemukan = false;

            cout << "Masukkan kode atau nama barang: ";
            getline(cin, input);

            input = trim(toLowerCase(input));

            bool isAngka = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    isAngka = false;
                    break;
                }
            }

            for (int i = 0; i < jumlahBarang; i++) {
                if (isAngka) {
                    int kodeCari = stoi(input);
                    if (barang[i].kode == kodeCari) {
                        cout << "Ditemukan: "
                             << barang[i].kode << " | "
                             << barang[i].nama << " | "
                             << barang[i].stok << " | "
                             << barang[i].harga << endl;
                        ditemukan = true;
                        break;
                    }
                } else {
                    string namaBarang = trim(toLowerCase(barang[i].nama));
                    if (namaBarang.find(input) != string::npos) {
                        cout << "Ditemukan: "
                             << barang[i].kode << " | "
                             << barang[i].nama << " | "
                             << barang[i].stok << " | "
                             << barang[i].harga << endl;
                        ditemukan = true;
                    }
                }
            }

            if (!ditemukan) {
                cout << "Barang tidak ditemukan.\n";
            }
            break;
        }

        // ===============================
        case 4: { // Transaksi Pembelian
            int kodeBeli, jumlahBeli;
            bool ditemukan = false;

            cout << "Kode Barang  : ";
            cin >> kodeBeli;

            cout << "Jumlah Beli  : ";
            cin >> jumlahBeli;
            clearInput();

            for (int i = 0; i < jumlahBarang; i++) {
                if (barang[i].kode == kodeBeli) {
                    ditemukan = true;

                    if (jumlahBeli > 0 && barang[i].stok >= jumlahBeli) {
                        barang[i].stok -= jumlahBeli;
                        int total = barang[i].harga * jumlahBeli;
                        totalPenjualan += total;

                        // Stack (LIFO)
                        if (top < 99)
                            stackTransaksi[++top] = barang[i].nama;

                        // Queue (FIFO)
                        if (rear < 99)
                            queuePembelian[++rear] = barang[i].nama;

                        cout << "Transaksi berhasil. Total: " << total << endl;
                    } else {
                        cout << "Stok tidak cukup atau jumlah tidak valid.\n";
                    }
                    break;
                }
            }

            if (!ditemukan) {
                cout << "Kode barang tidak ditemukan.\n";
            }
            break;
        }

        // ===============================
        case 5: { // Riwayat Transaksi (Stack)
            if (top < 0) {
                cout << "Belum ada transaksi.\n";
            } else {
                cout << "Riwayat Transaksi (LIFO):\n";
                for (int i = top; i >= 0; i--) {
                    cout << stackTransaksi[i] << endl;
                }
            }
            break;
        }

        // ===============================
        case 6: { // Proses Antrian (Queue)
            if (front > rear) {
                cout << "Antrian kosong.\n";
            } else {
                cout << "Diproses: " << queuePembelian[front] << endl;
                front++;
            }
            break;
        }

        // ===============================
        case 7: { // Cek Stok Menipis
            bool ada = false;
            for (int i = 0; i < jumlahBarang; i++) {
                if (barang[i].stok <= stokMinimum) {
                    cout << barang[i].nama
                         << " stok menipis (" << barang[i].stok << ")\n";
                    ada = true;
                }
            }
            if (!ada) {
                cout << "Tidak ada stok menipis.\n";
            }
            break;
        }

        // ===============================
        case 8: { // Laporan Penjualan
            cout << "Total Penjualan  : " << totalPenjualan << endl;
            cout << "Jumlah Transaksi : " << (top + 1) << endl;
            break;
        }

        }

    } while (pilihan != 0);

    return 0;
}
