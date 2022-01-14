

namespace MahasiswaService
{
    void Find(string kelas = "")
    {
        VariadicTable<int, string, string, string> vt({"No.", "NPM", "Nama", "Kelas"}, 4);

        vector<MahasiswaEntity> mahasiswa = MahasiswaRepository::Find(kelas);
        int i = 1;
        for (auto mhs : mahasiswa)
        {
            vt.addRow(i++, mhs.npm, mhs.nama, mhs.kelas);
        }
        if (i > 1)
        {

            vt.setColumnFormat({VariadicTableColumnFormat::AUTO,
                                VariadicTableColumnFormat::FIXED,
                                VariadicTableColumnFormat::AUTO,
                                VariadicTableColumnFormat::PERCENT});
            vt.setColumnPrecision({1, 3, 1, 2});
            vt.print(std::cout);
        }
        else
        {
            kotakPrinting("Data Mahasiswa Kosong");
        }
    }

    void Create()
    {
        MahasiswaEntity mahasiswa;

        input("NPM       : ", mahasiswa.npm, true, true);
        input("Nama      : ", mahasiswa.nama);
        input("Kode Kelas: ", mahasiswa.kelas);

        string msg = "\nMahasiswa dengan npm " + mahasiswa.npm;
        if (MahasiswaRepository::Create(mahasiswa))
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
        string npm;
        input("NPM : ", npm, true, true);
        MahasiswaRepository::Delete(npm);
        cout << "\nMahasiswa dengan NPM " + npm + " telah dihapus" << endl;
    }
}
