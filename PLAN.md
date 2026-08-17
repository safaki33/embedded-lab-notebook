# İlk 30 gün — çalışma programı

12 aylık derinleşme planının Faz 0 kısmı. Dört haftanın sonunda üç hattın da (güç mimarisi, RF,
Zephyr) kapısından girmiş, ölçüm defterini kurmuş ve ilk teknik yazıyı yayınlamış oluyorum.

Günlük ritim iki blok: sabah teori (~2 sa), akşam el işi (~1,5 sa). Haftada 6 gün, ~18 saat.

**Programın tek kuralı:** akşam bloğu iptal edilmez, sadece kısalır. Teori ertelendiğinde bir şey
kaybolmaz, el işi ertelendiğinde alışkanlık kurulmaz ve plan üçüncü haftada çöker.

---

## Hafta 1 — Ölçüm disiplini ve zemin

Amaç: alet kullanmayı değil, ölçüme güvenmeyi öğrenmek.

| Gün | Sabah | Akşam |
| --- | --- | --- |
| Pzt | Ölçüm defteri reposunu kur, sabit giriş şablonunu oturt | Prob kompanzasyonu; 1x ve 10x farkı, prob bant genişliğinin ölçülen yükselme zamanına etkisi |
| Sal | Ripple ölçüm metodolojisi: uzun toprak kablosunun sahte çınlaması, AC kuplaj, 20 MHz bant sınırı | Bir kartın 3,3 V rayını iki yöntemle ölç, iki görüntüyü yan yana kaydet |
| Çar | Açık kaynak bir kartın şemasını sayfa sayfa oku, anlamadığın blokları not al | O kartın güç ağacını kendi elinle çıkar: kaynak, koruma, regülatör tipleri, ray başına maks akım |
| Per | Datasheet disiplini: absolute maximum ile recommended operating farkı, grafiklerin alındığı koşullar | Güç ağacındaki bir LDO'nun dropout, PSRR ve termal yükselme hesabı |
| Cum | C hijyeni: volatile'ın yaptığı ve yapmadığı, atomik olmayan erişim, ISR paylaşımlı değişken tuzakları | Bilerek bir race condition üret, gözlemle, düzelt, ikisini de belgele |
| Cmt | Defter girdilerini temizle, ilk anlamlı commit | Telafi veya dinlenme |

**Hafta çıktısı:** repo, iki karşılaştırmalı ripple ölçümü, bir güç ağacı, bir LDO hesabı.

---

## Hafta 2 — Güç temelleri ve FreeRTOS iç yapısı

Amaç: ilk kez kağıt üstünde bir dönüştürücü tasarlamak.

| Gün | Sabah | Akşam |
| --- | --- | --- |
| Pzt | Erickson Bölüm 1-2: volt-saniye dengesi, kondansatör akım-saniye dengesi | Elle buck hesabı: 12 V → 3,3 V / 2 A. Görev oranı, ripple akımı, indüktör ve çıkış kondansatörü seçimi |
| Sal | Erickson Bölüm 3: eşdeğer devre modelleme ve verim | Kayıp bütçesi: iletim, anahtarlama, DCR, çekirdek. Toplam verim tahmini |
| Çar | CCM/DCM sınırı, senkron ve asenkron seçimi, hafif yükte atlama modları | Gerçek bir buck IC datasheet'iyle kendi hesabını karşılaştır, farkları açıkla |
| Per | FreeRTOS zamanlayıcı davranışı, sınırlı ve sınırsız öncelik tersinmesi | Üç görevli deney: H/M/L öncelik, binary semafor, durumları GPIO ile dışarı ver |
| Cum | Mutex ve öncelik kalıtımı; kaynak kodda mutex alma yolunu satır satır izle | Deneyi mutex ile çöz, önce/sonra zamanlamayı kaydet, gecikme farkını sayıyla yaz |
| Cmt | İlk teknik yazının taslağı: öncelik tersinmesini nasıl ürettim, ölçtüm, çözdüm | Telafi |

**Hafta çıktısı:** tam bir buck hesabı ve kayıp bütçesi, ölçülmüş öncelik tersinmesi deneyi, yazı taslağı.

---

## Hafta 3 — Zephyr, devicetree ve ilk driver

Amaç: Zephyr'ı kullanan değil, genişletebilen taraf olmak.

| Gün | Sabah | Akşam |
| --- | --- | --- |
| Pzt | Zephyr kurulumu ve west workspace mantığı: manifest, modüller, SDK | İlk build ve blinky; build çıktısındaki dosyaların ne olduğunu incele |
| Sal | Devicetree: node ve property yapısı, binding, board overlay, chosen | Blinky'nin LED'ini overlay ile başka pine taşı — tek satır C kodu değiştirmeden |
| Çar | Kconfig katmanları: varsayılanlar, prj.conf, board ve SoC seviyeleri | Logging alt sistemini aç, modül bazlı seviyeleri yapılandır |
| Per | Sürücü modeli: device yapısı, API tablosu, `DEVICE_DT_INST_DEFINE`, başlatma öncelikleri | Out-of-tree modül iskeleti: dizin yapısı, CMakeLists, Kconfig, manifest |
| Cum | Bir I2C sensör için binding yaz, property'leri devicetree'den okumayı çöz | Minimal driver'ı çalıştır ve logla; çalışmazsa önce binding'i kontrol et |
| Cmt | README'ye kurulum ve build talimatı, ekran görüntüsü, neden-ne açıklaması | Telafi |

**Hafta çıktısı:** çalışan Zephyr workspace, overlay ile taşınmış blinky, kendi yazdığın minimal sensör driver'ı.

---

## Hafta 4 — RF girişi ve konsolidasyon

Amaç: RF'i gizemli bir alan olmaktan çıkarmak.

| Gün | Sabah | Akşam |
| --- | --- | --- |
| Pzt | İletim hattı kavramı, karakteristik empedans, yansıma katsayısı, VSWR, S11'in fiziksel anlamı | Smith abağı: üç farklı yükü elle 50 Ω'a eşle (L, Pi, T ağlarından birer örnek) |
| Sal | VNA kalibrasyonu: açık, kısa, yük, geçiş standartları ve referans düzlemi | Kalibre et ve bir anteni ölç |
| Çar | Anten tipleri: ters-F, çip anten, monopol; toprak düzlemi uzunluğunun rezonansa etkisi | Aynı anteni serbest, el yakınında ve metale yakın ölç; rezonans kaymasını kaydet |
| Per | Mikroşerit ve koplanar hat hesapları, dielektrik sabiti, stack-up etkisi | Gerçek bir üretici stack-up'ıyla 50 Ω hat genişliğini hesapla, farklı stack-up'ta ne olduğunu gör |
| Cum | 30 günün tekrarı; defteri baştan oku, yarım kalanları listele ve telafi et | Teknik yazıyı yayınla |
| Cmt | 30. gün değerlendirmesi ve sonraki 60 günün planı | Serbest |

**Hafta çıktısı:** elle çözülmüş üç eşleme problemi, bir anten ölçümü, yayınlanmış ilk teknik yazı, 60 günlük plan.

---

## Her gün tekrarlayanlar

- Günün son 15 dakikası defter girdisi: ne denedin, ne ölçtün, ne anlamadın. Anlamadığın şey
  yarının ilk sorusu olur.
- Her hafta en az bir çıktı repoya girer. Boş hafta olmaz.
- Cuma akşamı 20 dakikalık retro: neyi planladın, neyi bitirdin, gelecek hafta neyi değiştireceksin.

## 30. gün sınavı

Hepsine rahat cevap verebiliyorsan Faz 1'e geç. Veremediğin konuya bir hafta daha ver.

| Soru | Hafta |
| --- | --- |
| Doğru ve yanlış ripple ölçümü arasındaki farkı kendi grafiğinle gösterebiliyor musun? | 1 |
| Bir buck'ın görev oranını, ripple akımını ve indüktör seçimini 10 dakikada yapabiliyor musun? | 2 |
| Öncelik tersinmesini bilerek üretip mutex ile çözebiliyor musun? | 2 |
| Zephyr'da bir pini tek satır C kodu değiştirmeden taşıyabiliyor musun? | 3 |
| S11 −6 dB olan bir antenle −14 dB olanın pratik farkını anlatabiliyor musun? | 4 |

---

Kitap bölüm numaraları Erickson & Maksimovic, *Fundamentals of Power Electronics* baskısına göredir.
