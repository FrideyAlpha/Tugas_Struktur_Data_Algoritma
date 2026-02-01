#include <iostream>
#include <string>
using namespace std;

// ===============================
// STRUCT DATA BARANG
// ===============================
// Struct digunakan untuk menyimpan data barang secara terkelompok
struct Barang {
    int kode;
    string nama;
    int stok;
    int harga;
};

// ===============================
// ARRAY DATA BARANG
// ===============================
// Array digunakan untuk menyimpan kumpulan barang
Barang barang[100];
int jumlahBarang = 0;

// ===============================
// STACK TRANSAKSI (LIFO)
// ===============================
// Stack digunakan untuk menyimpan riwayat transaksi pembelian
string stackTransaksi[100];
int top = -1;

// ===============================
// QUEUE PEMBELIAN (FIFO)
// ===============================
// Queue digunakan untuk antrian pembelian
string queuePembelian[100];
int front = 0;
int rear = -1;

// ===============================
// VARIABEL LAIN
// ===============================
int stokMinimum = 5;
int totalPenjualan = 0;

// ===============================
// FUNGSI MENU
// ===============================
void tampilMenu() {
    cout << "\n=== TOKOKU INVENTORY MANAGER ===\n";
    cout << "1. Tambah Barang\n";
    cout << "2. Lihat Semua Barang\n";
    cout << "3. Cari Barang\n";
    cout << "4. Transaksi Pembelian\n";
    cout << "5. Riwayat Transaksi\n";
    cout << "6. Proses Antrian\n";
    cout << "7. Cek Stok Menipis\n";
    cout << "8. Laporan Penjualan\n";
    cout << "0. Keluar\n";
    cout << "Pilih menu: ";
}

// ===============================
// PROGRAM UTAMA
// ===============================
int main() {
    int pilihan;

    do {
        tampilMenu();
        cin >> pilihan;

        switch (pilihan) {

        case 1: // Tambah Barang
            cout << "Kode Barang  : ";
            cin >> barang[jumlahBarang].kode;
            cout << "Nama Barang  : ";
            cin >> barang[jumlahBarang].nama;
            cout << "Stok         : ";
            cin >> barang[jumlahBarang].stok;
            cout << "Harga        : ";
            cin >> barang[jumlahBarang].harga;

            jumlahBarang++;
            cout << "Barang berhasil ditambahkan\n";
            break;

        case 2: // Lihat Barang
            for (int i = 0; i < jumlahBarang; i++) {
                cout << barang[i].kode << " | "
                     << barang[i].nama << " | "
                     << barang[i].stok << " | "
                     << barang[i].harga << endl;
            }
            break;

        case 3: { 
            // ===============================
            // PENCARIAN BARANG BERDASARKAN KODE / NAMA
            // ===============================
            string inputCari;
            bool ditemukan = false;

            cout << "Masukkan kode atau nama barang: ";
            cin >> inputCari;

            // Cek apakah input berupa angka (kode barang)
            bool isAngka = true;
            for (char c : inputCari) {
                if (!isdigit(c)) {
                    isAngka = false;
                    break;
                }
            }

            for (int i = 0; i < jumlahBarang; i++) {

                // Jika input angka → cari berdasarkan kode
                if (isAngka) {
                    int kodeCari = stoi(inputCari);
                    if (barang[i].kode == kodeCari) {
                        cout << "Ditemukan: "
                            << barang[i].kode << " | "
                            << barang[i].nama << " | "
                            << barang[i].stok << " | "
                            << barang[i].harga << endl;
                        ditemukan = true;
                    }
                }
                // Jika input teks → cari berdasarkan nama
                else {
                    if (barang[i].nama == inputCari) {
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


        case 4: { // Transaksi Pembelian
            int kodeBeli, jumlahBeli;
            cout << "Kode Barang: ";
            cin >> kodeBeli;
            cout << "Jumlah Beli: ";
            cin >> jumlahBeli;

            for (int i = 0; i < jumlahBarang; i++) {
                if (barang[i].kode == kodeBeli && barang[i].stok >= jumlahBeli) {
                    barang[i].stok -= jumlahBeli;
                    totalPenjualan += barang[i].harga * jumlahBeli;

                    // Push ke stack
                    top++;
                    stackTransaksi[top] = barang[i].nama;

                    // Enqueue ke queue
                    rear++;
                    queuePembelian[rear] = barang[i].nama;

                    cout << "Transaksi berhasil\n";
                }
            }
            break;
        }

        case 5: // Riwayat Transaksi
            for (int i = top; i >= 0; i--) {
                cout << stackTransaksi[i] << endl;
            }
            break;

        case 6: // Proses Antrian
            if (front <= rear) {
                cout << "Diproses: " << queuePembelian[front] << endl;
                front++;
            } else {
                cout << "Antrian kosong\n";
            }
            break;

        case 7: // Stok Menipis
            for (int i = 0; i < jumlahBarang; i++) {
                if (barang[i].stok <= stokMinimum) {
                    cout << barang[i].nama << " stok menipis\n";
                }
            }
            break;

        case 8: // Laporan
            cout << "Total Penjualan: " << totalPenjualan << endl;
            break;
        }

    } while (pilihan != 0);

    return 0;
}
