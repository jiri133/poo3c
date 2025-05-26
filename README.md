
## 🎮 Fish Food Frenzy — Reimagined

Aceasta este o reinterpretare a clasicului joc *Fish Food Frenzy*, scrisă în C++. Jucătorul controlează un pește care trebuie să supraviețuiască și să evolueze într-un ecosistem plin de prădători și recompense. Mecanica principală este simplă, dar captivantă: **mănâncă pești mai mici pentru a deveni mai mare** și evită să fii mâncat de cei mai mari.

### 🐟 Reguli de bază:

* Peștele tău începe mic, dar poate crește și evolua (Reptilă, Amfibian).
* Poți mânca doar pești mai mici decât tine.
* Dacă încerci să mănânci un pește mai mare, vei muri.
* Există **niveluri de dificultate** (Sunrise, Noon, Midnight) care afectează cât de mulți pești mari apar în acvariu.
* **Recompense speciale** pot apărea în timpul jocului:

  * `Invincible`: poți mânca orice pește fără riscuri pentru o tură.
  * `Double Points`: scorul obținut este dublu pentru o perioadă limitată.

### 🚧 În curs de dezvoltare:

* Comportamente avansate pentru pești mari (ex: te atacă dacă te apropii).
* Timer pentru recompense.
* Mai multe tipuri de evoluție și abilități speciale.


## Tema 2

#### Cerințe
- [x] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ] moșteniri:
  - [x] minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [ ] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [ ] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [ ] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [x] smart pointers (recomandat, opțional)
- [ ] excepții
  - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [ ] funcții și atribute `static`
- [ ] STL
- [ ] cât mai multe `const`
- [ ] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [ ] minim 75-80% din codul propriu să fie C++
- [ ] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [ ] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.2`
