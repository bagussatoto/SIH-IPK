

namespace MataKuliahService
{
    void Find()
    {
        VariadicTable<int, string, string, string> vt({"No.", "Kode Matkul", "Mata Kuliah", "Kelas"}, 4);

        vector<MataKuliahEntity> matkul = MataKuliahRepository::Find();
        int i = 1;
        for (auto mk : matkul)
        {
            vt.addRow(i++, mk.kodeMatkul, mk.mataKuliah, mk.dosenPengampu);
        }
        if (i > 1)
        {
            vt.setColumnFormat({VariadicTableColumnFormat::AUTO,
                                VariadicTableColumnFormat::FIXED,
                                VariadicTableColumnFormat::AUTO,
                                VariadicTableColumnFormat::AUTO});
            vt.setColumnPrecision({1, 3, 1, 2});
            vt.print(std::cout);
        }
        else
        {
            kotakPrinting("Data Mata Kuliah Kosong");
        }
    }

    void Create()
    {
        MataKuliahEntity matkul;

        input("Kode Matkul    : ", matkul.kodeMatkul, true, true);
        input("Mata Kuliah    : ", matkul.mataKuliah);
        input("Dosen Pengampu : ", matkul.dosenPengampu);

        string msg = "\nMataKuliahEntity dengan kodeMatkul " + matkul.kodeMatkul;
        if (MataKuliahRepository::Create(matkul))
        {

            msg += " telah tersimpan";
        }
        else
        {

            msg += " sudah ada";
        }

        cout << msg;
        enter(1);
    }

    void Delete()
    {
        string kodeMatkul;
        input("Kode Matkul : ", kodeMatkul, true, true);
        MataKuliahRepository::Delete(kodeMatkul);
        cout << "\nMata kuliah dengan kode matkul " + kodeMatkul + " telah dihapus" << endl;
    }
}
