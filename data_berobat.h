#ifndef data_berobat_h
#define data_berobat_h

#include <iostream>
#include <string>
using namespace std;

// Data Pasien (Child)



// Data Dokter (Parent)
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
    adrRelasi firstRelasi; 
};

struct ListDokter {
    adrDokter first;
    adrDokter last;
};

// Data Relasi
typedef struct elmRelasi *adrRelasi;
struct elmRelasi {
    adrRelasi next;
    adrRelasi child;
};

// Manajemen Dokter
void createListDokter(ListDokter &L);
adrDokter alokasiDokter(string nama, string spesialisasi);
void insertLastDokter(ListDokter &L, adrDokter P);
void insertFirstDokter(ListDokter &L, adrDokter &P);
void deleteDokter(ListDokter &L, string nama);
adrDokter findDokter(ListDokter L, string nama);
void showAllDokter(ListDokter L);

// Manajemen Pasien



// Manajemen Relasi
void connectPasienToDokter(ListDokter &LD, ListPasien &LP, string namaDokter, string namaPasien);
void showAllData (ListDokter LD);

//Mencari data child (pasien) pada parent tertentu

//Menghapus data child (pasien) pada parent tertentu

// Menghitung jumlah data child dari parent tertentu

#endif