// KANAHAYA EZI TALITHA BELVA
// 124250046
// SI-C

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

struct karyawan
{
    char id[10];
    char nama[50];
};

struct barang
{
	char nama[50];
	int harga;
	int stok;
};

// batas maksimum data
const int MAX = 1000;

// fungsi untuk mengecek apakah input berupa angka
bool inputAngka(int &nilai)
{
    cin >> nilai;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }

    return true;
}

// fungsi untuk membaca file karyawan
int bacaKaryawan(karyawan data[])
{
    FILE *file = fopen("karyawan.txt", "r");

    if (file == NULL)
    {
        return 0;
    }

    int i = 0;

    while (i < MAX && fscanf(file, "%s %s", data[i].id, data[i].nama) == 2)
	{
		i++;
	}

    fclose(file);

    return i;
}

// fungsi untuk menambah data karyawan
void tambahKaryawan()
{
	system("cls");
	
    FILE *file = fopen("karyawan.txt", "a");

    if (file == NULL)
    {
        cout << "File tidak bisa dibuka.\n";
        system("pause");
        return;
    }

    int jml;
    karyawan data[MAX];
    karyawan dataLama[MAX];
	int jumlahLama = bacaKaryawan(dataLama);

    cout << "Masukkan jumlah karyawan: ";
    if (!inputAngka(jml))
    {
        cout << "Input harus berupa angka.\n\n";
        fclose(file);
        system("pause");
        return;
    }
    
   if (jml <= 0)
    {
		cout << "Input harus lebih dari 0.\n\n";
        fclose(file);
        system("pause");
        return;
	}
    
	if (jumlahLama + jml > MAX)
	{
		cout << "Data karyawan melebihi batas.\n";
		cout << "Data yang sudah ada: " << jumlahLama << endl;
		cout << "Maksimal tambah lagi: " << MAX - jumlahLama << endl;
		cout << endl;
		fclose(file);
		system("pause");
		return;
	}
	else
	{
		for (int i = 0; i < jml; i++)
		{
			karyawan *p = &data[i];
			cout << endl;
			cout << "ID karyawan\t: ";
			cin >> p->id;
			cout << "Nama karyawan\t: ";
			cin >> p->nama;
			cout << endl;

			fprintf(file, "%s %s\n", p->id, p->nama);
		}

		fclose(file);
		cout << "Data berhasil disimpan!\n";
	}
    
    cout << endl;
    
    system("pause");
}

// fungsi untuk melihat seluruh data karyawan
void lihatKaryawan()
{
	system("cls");
	
    FILE *file = fopen("karyawan.txt", "r");

    if (file == NULL)
    {
        cout << "Belum ada data karyawan.\n";
        system("pause");
        return;
    }

    karyawan data;
    int no = 1;

    cout << "===== DATA KARYAWAN =====\n\n";
    
    while (fscanf(file, "%s %s", data.id, data.nama) == 2)
    {
        cout << "Karyawan ke-" << no << endl;
        cout << "ID\t: " << data.id << endl;
        cout << "Nama\t: " << data.nama << endl;
        cout << endl;

        no++;
    }
    
    fclose(file);
    
    system("pause");
}

// fungsi untuk mencari data karyawan berdasarkan ID
void cariKaryawan()
{
	system("cls");
	
    FILE *file = fopen("karyawan.txt", "r");

    if (file == NULL)
    {
        cout << "Belum ada data karyawan.\n";
        system("pause");
        return;
    }

    int ketemu = 0;
    char cariId[10];
    karyawan data;

    cout << "Masukkan ID karyawan yang dicari: ";
    cin >> cariId;

    while (fscanf(file, "%s %s", data.id, data.nama) == 2)
    {
        if (strcmp(data.id, cariId) == 0)
        {
			cout << endl;
            cout << "Data ditemukan!\n";
            cout << "ID\t: " << data.id << endl;
            cout << "Nama\t: " << data.nama << endl;
            ketemu = 1;
            break;
        }
    }
    
    if (ketemu == 0)
    {
        cout << "Data tidak ditemukan.\n";
    }
    
    fclose(file);
    
    cout << endl;
    
    system("pause");
}

void menuAdmin()
{
    int pilihan = 0;
    
    do
    {
		system("cls");

		cout << "===========================\n";
		cout << "\tHalo Admin!\n";
		cout << "===========================\n";
		cout << "1. Tambah data karyawan\n";
		cout << "2. Lihat data karyawan\n";
		cout << "3. Cari data karyawan\n";
		cout << "4. Logout\n";
		cout << "===========================\n";

        cout << "Pilih menu: ";
        if (!inputAngka(pilihan))
		{
			cout << "Input harus berupa angka.\n\n";
			system("pause");
			continue;
		}

        switch (pilihan)
        {
        case 1:
            tambahKaryawan();
            break;
        case 2:
            lihatKaryawan();
            break;
        case 3:
            cariKaryawan();
            break;
        case 4:
            cout << "Keluar dari menu admin..\n\n";
            system("pause");
            break;
        default:
            cout << "Pilihan tidak tersedia.\n\n";
            system("pause");
		}
    } 
    while (pilihan != 4);
}

// fungsi login admin
void loginAdmin()
{
	system("cls");
	
    char inputUsn[10];
    char inputPw[10];
    char username[10] = "admin";
    char password[10] = "123";

    do
    {
        cout << "Masukkan Username anda\t: ";
        cin >> inputUsn;
        cout << "Masukkan Password anda\t: ";
        cin >> inputPw;
        
		// cek username dan password
        if (strcmp(inputUsn, username) != 0 || strcmp(inputPw, password) != 0)
        {
            cout << "Username atau Password anda salah,\n";
            cout << "silahkan coba lagi.\n\n";
            system("pause");
        }
        else 
        {
			cout << "Berhasil login!\n\n";
			system("pause");
            menuAdmin();
            break;
        }
    } 
    while (true);
}

// fungsi untuk membaca file barang
int bacaBarang(barang data[])
{
	FILE *file = fopen("barang.txt", "r");

    if (file == NULL)
    {
        return 0;
    }

    int i = 0;

    while (i < MAX && fscanf(file, "%s %d %d", data[i].nama, &data[i].harga, &data[i].stok) == 3)
    {
        i++;
    }
    
    fclose(file);
    
    return i;
}

// fungsi untuk menambah data barang
void tambahBarang()
{
	system("cls");
	
    FILE *file = fopen("barang.txt", "a");

    if (file == NULL)
    {
        cout << "File tidak bisa dibuka.\n";
        system("pause");
        return;
	}

    int jml;
    barang data[MAX];
    barang dataLama[MAX];
	int jumlahLama = bacaBarang(dataLama);

    cout << "Masukkan jumlah barang: ";
    if (!inputAngka(jml))
    {
        cout << "Input harus berupa angka.\n\n";
        fclose(file);
        system("pause");
        return;
    }
    
    if (jml <= 0)
    {
		cout << "Input harus lebih dari 0.\n\n";
        fclose(file);
        system("pause");
        return;
	}
    
	if (jumlahLama + jml > MAX)
	{
		cout << "Data barang melebihi batas.\n";
		cout << "Data yang sudah ada: " << jumlahLama << endl;
		cout << "Maksimal tambah lagi: " << MAX - jumlahLama << endl;
		cout << endl;
		fclose(file);
		system("pause");
		return;
	}
	else
	{
		for (int i = 0; i < jml; i++)
		{
			barang *p = &data[i];
			
			cout << endl;
			cout << "Barang ke-" << i + 1 << endl;
			
			cout << "Nama Barang\t: ";
			cin >> p->nama;
			
			cout <<"Harga Barang\t: ";
			if (!inputAngka(p->harga))
			{
				cout << "Harga harus berupa angka.\n\n";
				fclose(file);
				system("pause");
				return;
			}
		
			if (p->harga <= 0)
			{
				cout << "Harga harus lebih dari 0.\n\n";
				fclose(file);
				system("pause");
				return;
			}
			
			cout << "Stok Barang\t: ";
			if (!inputAngka(p->stok))
			{
				cout << "Stok harus berupa angka.\n\n";
				fclose(file);
				system("pause");
				return;
			}

			if (p->stok <= 0)
			{
				cout << "Stok harus lebih dari 0.\n\n";
				fclose(file);
				system("pause");
				return;
			}

			fprintf(file, "%s %d %d\n", p->nama, p->harga, p->stok);
		}
			
		fclose(file);
		
		cout << endl;	
		cout << "Data berhasil disimpan!\n\n";
	}
    
    system("pause");
}

// bubble sort ascending 
// untuk mengurutkan barang berdasarkan harga (kecil ke besar)
void bubbleSortAsc(barang data[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (data[j].harga > data[j + 1].harga)
            {
                barang temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

// fungsi partition (membagi data) untuk quick sort
int partition(barang data[], int low, int high)
{
    int pivot = data[high].harga;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (data[j].harga > pivot)
        {
            i++;

            barang temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    
    barang temp = data[i + 1];
    data[i + 1] = data[high];
    data[high] = temp;

    return i + 1;
}

// quick sort descending 
// untuk mengurutkan berdasarkan harga (besar ke kecil)
void quickSortDesc(barang data[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(data, low, high);

        quickSortDesc(data, low, pi - 1);
        quickSortDesc(data, pi + 1, high);
    }
}

// fungsi untuk melihat data barang dengan pilihan sorting
void lihatBarang()
{
	system("cls");
	
    barang data[MAX];
    int jumlah = bacaBarang(data);

    if (jumlah == 0)
    {
        cout << "Belum ada data barang.\n";
        system("pause");
        return;
    }

    int pilihan = 0;
    
    cout << "1. Ascending\n";
    cout << "2. Descending\n";
    
    cout << "Pilih sorting: ";
    if (!inputAngka(pilihan))
	{
		cout << "Input harus berupa angka.\n\n";
		system("pause");
		return;
	}

    switch (pilihan)
    {
    case 1:
        bubbleSortAsc(data, jumlah);
        break;
    case 2:
        quickSortDesc(data, 0, jumlah - 1);
        break;
    default:
        cout << "Pilihan tidak tersedia.\n\n";
        system("pause");
        return;
    }
    
    for (int i = 0; i < jumlah; i++)
    {
		cout << endl;
        cout << "Data barang ke-" << i + 1 << endl;
        cout << "Nama\t: " << data[i].nama << endl;
        cout << "Harga\t: " << data[i].harga << endl;
        cout << "Stok\t: " << data[i].stok << endl;
        cout << "===========================\n";
    }
    
    system("pause");
}

// fungsi untuk menyimpan ulang data barang ke file
void simpanBarang(barang data[], int jumlah)
{
	FILE *file = fopen("barang.txt", "w");

    if (file == NULL)
    {
        cout << "File tidak bisa dibuka.\n";
        system("pause");
        return;
    }

    for (int i = 0; i < jumlah; i++)
    {
        fprintf(file, "%s %d %d\n", data[i].nama, data[i].harga, data[i].stok);
    }

    fclose(file);
}

// fungsi untuk mengedit data barang
void editBarang()
{
	system("cls");

    barang data[MAX];
    int jumlah = bacaBarang(data);

    if (jumlah == 0)
    {
        cout << "Data barang belum ada.\n";
        system("pause");
        return;
    }

    char cariNama[50];
    int ketemu = 0;

    cout << "Masukkan nama barang yang ingin diedit: ";
    cin >> cariNama;

    for (int i = 0; i < jumlah; i++)
    {
        if (strcmp(data[i].nama, cariNama) == 0)
        {
			cout << endl;
            cout << "Data ditemukan!\n";
            cout << "Nama\t: " << data[i].nama << endl;
            cout << "Harga\t: " << data[i].harga << endl;
            cout << "Stok\t: " << data[i].stok << endl;

			cout << endl;
            cout << "Masukkan data baru\n";
            cout << "Nama Barang\t: ";
            cin >> data[i].nama;
            
            cout << "Harga Barang\t: ";
            if (!inputAngka(data[i].harga))
			{
				cout << "Harga harus berupa angka.\n";
				system("pause");
				return;
			}
			if (data[i].harga <= 0)
			{
				cout << "Harga harus lebih dari 0.\n";
				system("pause");
				return;
			}
			
            cout << "Stok Barang\t: ";
            if (!inputAngka(data[i].stok))
			{
				cout << "Stok harus berupa angka.\n";
				system("pause");
				return;
			}
			if (data[i].stok <= 0)
			{
				cout << "Stok harus lebih dari 0.\n";
				system("pause");
				return;
			}

            ketemu = 1;
            break;
        }
    }

    if (ketemu == 1)
    {
        simpanBarang(data, jumlah);
        cout << endl;
        cout << "Data berhasil diupdate!\n\n";
    }
    else
    {
        cout << "Data barang tidak ditemukan.\n";
    } 
    
    system("pause");
}

// sequential search untuk mencari barang berdasarkan nama
void sequentialSearch()
{
    barang data[MAX];
    int jumlah = bacaBarang(data);

    if  (jumlah == 0)
    {
        cout << "Belum ada data barang.\n";
        system("pause");
        return;
    }

    char cariNama[50];
    int ketemu = 0;
	
	cout << endl;
    cout << "Masukkan nama barang: ";
    cin >> cariNama;

    for (int i = 0; i < jumlah; i++)
    {
        if (strcmp(data[i].nama, cariNama) == 0)
        {
			cout << endl;
            cout << "Data ditemukan!\n";
            cout << "Nama\t: " << data[i].nama << endl;
            cout << "Harga\t: " << data[i].harga << endl;
            cout << "Stok\t: " << data[i].stok << endl;
            cout << endl;

            ketemu = 1;
            break;
        }
    }

    if (ketemu == 0)
    {
        cout << "Data tidak ditemukan.\n\n";
    }
    
    system("pause");
}

// binary search untuk mencari barang berdasarkan nama
void binarySearch()
{
    barang data[MAX];
    int jumlah = bacaBarang(data);

    if (jumlah == 0)
    {
        cout << "Belum ada data barang.\n";
        system("pause");
        return;
    }

    // mengurutkan nama barang
    for (int i = 0; i < jumlah - 1; i++)
    {
        for (int j = 0; j < jumlah - i - 1; j++)
        {
            if (strcmp(data[j].nama, data[j + 1].nama) > 0)
            {
                barang temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    char cariNama[50];
    int kiri = 0;
    int kanan = jumlah - 1;
    int tengah;
    int ketemu = 0;

	cout << endl;
    cout << "Masukkan nama barang: ";
    cin >> cariNama;

    while (kiri <= kanan)
    {
        tengah = (kiri + kanan) / 2;
        
        if (strcmp(data[tengah].nama, cariNama) == 0)
        {
			cout << endl;
            cout << "Data ditemukan!\n";
            cout << "Nama\t: " << data[tengah].nama << endl;
            cout << "Harga\t: " << data[tengah].harga << endl;
            cout << "Stok\t: " << data[tengah].stok << endl;
            cout << endl;

            ketemu = 1;
            break;
        }
        else if (strcmp(data[tengah].nama, cariNama) < 0)
        {
            kiri = tengah + 1;
        }
        else
        {
            kanan = tengah - 1;
        }
    }

    if (ketemu == 0)
    {
        cout << "Data tidak ditemukan.\n\n";
        system("pause");
        return;
    }
    
    system("pause");
}

// menu pencarian barang
void cariBarang()
{
	system("cls");
	
	int pilihan = 0;

    cout << "1. Sequential Search\n";
    cout << "2. Binary Search\n";
    
    cout << "Pilih metode: ";
    if (!inputAngka(pilihan))
	{
		cout << "Input harus berupa angka.\n\n";
		system("pause");
		return;
	}

    switch (pilihan)
    {
    case 1:
        sequentialSearch();
        break;
    case 2:
        binarySearch();
        break;
    default:
        cout << "Pilihan tidak tersedia.\n\n";
        system("pause");
        return;
    }
}

// menu karyawan
void menuKaryawan()
{
	int pilihan = 0;
    
    do
    {
		system("cls");
		cout << "===========================\n";
		cout << "\tHalo Karyawan!\n";
		cout << "===========================\n";
		cout << "1. Tambah data barang\n";
		cout << "2. Lihat data barang\n";
		cout << "3. Edit data barang\n";
		cout << "4. Cari data barang\n";
		cout << "5. Logout\n";
		cout << "===========================\n";
		
		cout << "Pilih menu: ";
		if (!inputAngka(pilihan))
		{
			cout << "Input harus berupa angka.\n\n";
			system("pause");
			continue;
		}
		
		switch (pilihan)
        {
        case 1:
            tambahBarang();
            break;
        case 2:
            lihatBarang();
            break;
        case 3:
            editBarang();
            break;
        case 4:
            cariBarang();
            break;
        case 5:
            cout << "Keluar dari menu karyawan..\n\n";
            system("pause");
            break;
        default:
            cout << "Pilihan tidak tersedia.\n\n";
            system("pause");
		}
    } 
    while (pilihan != 5);
}

// fungsi utama program
int main()
{
    int pilihan = 0;
    
    do
    {
		system("cls");
		
		cout << "====== WELCOME TO COCOA HEAVEN ======\n";
		cout << "1. Login Admin\n";
		cout << "2. Karyawan\n";
		cout << "3. Keluar\n";
		cout << "=====================================\n";

        cout << "Masukan pilihan menu: ";
        if (!inputAngka(pilihan))
		{
			cout << "Input harus berupa angka.\n\n";
			system("pause");
			continue;
		}

        switch(pilihan)
        {
            case 1:
                loginAdmin();
                break;
            case 2:
                menuKaryawan();
                break;
            case 3:
                cout << "Keluar dari program..\n";
                return 0;
            default:
                cout << "Pilihan tidak tersedia.\n\n";
                system("pause");
        }
    }
    while (pilihan != 3);
}

// Alhamdulillah selesai
