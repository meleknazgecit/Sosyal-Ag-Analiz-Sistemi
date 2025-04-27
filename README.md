# Sosyal Ağ Analiz Sistemi

Bu proje, sosyal ağlar üzerinde analiz yapabilmek için **Red-Black Tree** veri yapısını kullanan bir C programıdır. Kullanıcılar, arkadaşlık ilişkileri ve topluluklar üzerine analiz yapabilir. Ayrıca, kullanıcı etkisi, arkadaş mesafesi ve topluluk tespiti gibi özellikler sunar.

## Özellikler

- **Kullanıcı Yönetimi**  
  Kullanıcılar, `Red-Black Tree` veri yapısına eklenerek sosyal ağa kaydedilir.

- **Arkadaşlık İlişkileri**  
  İki kullanıcı arasında arkadaşlık bağlantıları kurulur.

- **Mesafe Analizi**  
  Bir kullanıcının:
  - **Mesafe 1 (Doğrudan arkadaşlar)**  
  - **Mesafe 2 (Arkadaşın arkadaşı)**  
  olan arkadaşlarını bulur ve listeler.

- **Kullanıcı Etkisi**  
  Kullanıcının sosyal ağda ne kadar etkili olduğunu hesaplar.

- **Ortak Arkadaş Analizi**  
  İki kullanıcı arasında ortak arkadaşları bulur ve listeler.

- **Topluluk Tespiti**  
  Kullanıcının ait olduğu sosyal topluluğu belirler ve topluluk üyelerini listeler.
 
## Kullanım
1. Programı çalıştırın.
2. Program, sizden bir kullanıcı ID'si girmenizi ister. Girilen ID'ye göre:
Arkadaşlık analizi yapılır ve Mesafe 1 ve Mesafe 2 arkadaşlar listelenir.
Kullanıcının etkisi hesaplanır.
3. Ardından, ortak arkadaş analizi yapmanız için ikinci bir kullanıcı ID'si girmeniz istenir.
4. Son olarak, sosyal ağdaki topluluklar tespit edilir ve listelenir.

**Örnek Çıktı**
Arkadaslarini analiz etmek istediginiz kullanici ID'sini girin: 103
Kullanici ID: 103
Mesafe 1 arkadaslar: 101 104
Mesafe 2 arkadaslar: 105
Kullanici etkisi: 3
Ortak arkadas analizi icin ikinci ID'yi girin: 104
Ortak Arkadaslari Bulunan ID'ler (103 104):
Ortak arkadas sayisi: 0
Topluluk tespitine geciliyor:
Topluluk: 103 101 105 102 106 104

## Veri Seti Yapısı
Program, kullanıcıları ve arkadaşlık ilişkilerini veriseti.txt adlı dosyadan okur. Örnek bir veri seti aşağıdaki gibidir:
# Kullanıcılar
USER 101
USER 102
USER 103
USER 104
USER 105
USER 106

# Arkadaşlık İlişkileri
FRIEND 101 103
FRIEND 101 105
FRIEND 102 105
FRIEND 103 104
FRIEND 104 101
FRIEND 105 106
FRIEND 106 102
