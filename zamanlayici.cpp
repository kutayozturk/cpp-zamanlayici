#include <iostream>
#include <chrono>  // Zaman ölçümü için
#include <thread>  // Thread kullanımı için
#include <cstdlib> // system() fonksiyonu için (Linux/macOS için)

#ifdef _WIN32
#include <windows.h> // Windows'ta Beep fonksiyonu için
#endif

void sesli_alarm()
{
    // Alarm 3 kez çalsın
    for (int i = 0; i < 3; i++)
    {
// Windows'ta Beep kullanılır
#ifdef _WIN32
        Beep(1000, 1000); // 1000 Hz frekansında 1 saniye çalar
#else
// Linux/macOS için ses dosyası çalma
#ifdef __linux__
        system("aplay /path/to/sound.wav"); // Linux için ses dosyasını çal
#elif __APPLE__
        system("afplay /path/to/sound.mp3"); // macOS için ses dosyasını çal
#endif
#endif

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Bir saniye bekler
    }
}

void zamanlayici(int sure, std::string birim)
{
    int toplam_saniye = 0;

    // Zaman birimine göre saniyeye çevirme
    if (birim == "saniye")
    {
        toplam_saniye = sure;
    }
    else if (birim == "dakika")
    {
        toplam_saniye = sure * 60;
    }
    else if (birim == "saat")
    {
        toplam_saniye = sure * 3600;
    }

    // Geri sayım yapalım
    for (int i = toplam_saniye; i >= 0; i--)
    {
        int dakika = i / 60; // Dakikayı hesapla
        int saniye = i % 60; // Saniyeyi hesapla

        std::cout << "Kalan zaman: " << dakika << " dakika " << saniye << " saniye\r";
        std::cout.flush();                                    // Ekranı güncelle
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 1 saniye bekle
    }

    std::cout << "\nZamanlayıcı süresi doldu! Alarm çalıyor..." << std::endl;
    sesli_alarm(); // Sesli alarm çal
}

int main()
{

    setlocale(LC_ALL, "tr_TR.UTF-8");

    int sure;
    std::string birim;

    std::cout << "Lütfen zaman birimi seçin: (saniye/dakika/saat): ";
    std::cin >> birim; // Kullanıcıdan birim seçimi al

    std::cout << "Lütfen süreyi girin (" << birim << " cinsinden): ";
    std::cin >> sure; // Kullanıcıdan süreyi al

    // Zamanlayıcıyı başlat
    zamanlayici(sure, birim);

    return 0;
}
