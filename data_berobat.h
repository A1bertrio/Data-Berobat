#ifndef data_berobat_h
#define data_berobat_h

#include <iostream>
#include <string>
using namespace std;

struct elmPasien;
typedef elmPasien* adrPasien;

// Data Relasi - Single Linked List
typedef struct elmRelasi *adrRelasi;
struct elmRelasi {
    adrRelasi next;
    adrPasien child; // pointer ke data pasien (child)
};

// Data Dokter (Parent) - Double Linked List
struct Dokter {
    string nama_dokter;
    string spesialisasi;
    int jumlah_pasien;
};

typedef struct elmDokter* adrDokter;

struct elmDokter {
    Dokter info;
    adrDokter next;
    adrDokter prev;
    adrRelasi firstRelasi; // head dari list relasi
};

struct ListDokter {
    adrDokter first;
    adrDokter last;
};
// Data Pasien (Child) - Single Linked List
struct Pasien {
    string nama_pasien;
    int umur;
    string keluhan;
    int jumlah_dokter; // maksimal 5 dokter
};



struct elmPasien {
    Pasien info;
    adrPasien next;
    adrPasien prev;  
};

struct ListPasien {
    adrPasien first;
    adrPasien last;
};

// Manajemen Dokter
void createListDokter(ListDokter &L);
adrDokter alokasiDokter(string nama, string spesialisasi);
void insertLastDokter(ListDokter &L, adrDokter P);
void deleteDokter(ListDokter &L, string nama); // menghapus dokter beserta semua relasinya
adrDokter findDokter(ListDokter L, string nama); 
void showAllDokter(ListDokter L); // ,emankan semua data dokter tanpa pasien

// Manajemen Relasi
void connect(ListDokter &LD, ListPasien &LP, string namaDokter, string namaPasien); // c. connect parent dengan child (dan sebaliknya)
void showPasienByDokter (ListDokter LD, string namaDokter); // g. Menampilkan data pasien yang ditangani dokter tertentu
void showDokterByPasien (ListDokter LD, ListPasien LP, string namaPasien); // h. Menampilkan data dokter yang menangani pasien tertentu
void showDokterSibuk (ListDokter LD); // i. Menampilkan data dokter yang tidak sibuk dan yang paling sibuk

// Manajemen Pasien
void createListPasien(ListPasien &L);
adrPasien alokasiPasien(string nama, int umur, string keluhan);
void insertFirstPasien(ListPasien &L, adrPasien P);
adrPasien findPasien(ListPasien L, string nama);
void deletePasien(ListPasien &LP, ListDokter &LD, string nama);
void showAllPasienWithDokter(ListPasien LP, ListDokter LD);

#endif