# Conpoa
Za razliku od uobičajenih metoda dobivanja konsenzusa (koja mogu prikazati akcije supstitucije i dodavanja/brisanja), koristeći usmjerene grafove moguće je prizati složenije promjene u evoluciji slijeda, kao što su translacija domene, duplikacija i rekombinacija. Implementacija ovog rada nudi mogućnost stvaranja više konsenzusnih sljedova iz grafova djelomično uređenih višestrukih poravnanja koristeći format zapisa programskog alata POA. Stvoreni konsenzusi nisu ograničeni na lokalne promjene zbog veće mogućnosti prikaza informacija pomoću usmjerenih grafova. 

Za dobivanje konsenzusa iz usmjerenih grafova napravljen je program Conpoa.

Trenutno je podržan samo format .po kojeg stvara program poa kojeg se može instalirati na linux računalima pomoću naredbe ```
sudo apt-get install poa
```ili skinuti cijeli izvorni kod sa http://sourceforge.net/projects/poamsa/.

Za dobiti .po format može se iskoristiti naredba:
```
 poa -read_fasta a_fasta_file.fa -po a_po_file.po blosum80.mat
``` 
blosum80.mat se može pronaći u datoteci sa izvornim kodom.

Ulazni format pravila je specifičan za Conpoa. Trenutno postoje dva podržana pravila, postotak sadržanosti slijeda u konsenzusu i najveća dozvoljena rupa u poravnanju ne brojeći neporavnate rubove.
Pravila se definiraju svaka u svojem redu.
Primjer:
```
seq_percentage_in_consensus <minimal_percentage> <maximal_precentage>
internal_gap_length <limit>
``` 

<h3>Kompajliranje</h3>
Za dobiti izvršivi kod potreban je CMake. Potrebno je izvršiti naredbe:
```
cmake CMakeLists.txt 
make
```
U trenutnom direktoriju stvorit će se izvršiva datoteka ```conpoa```.

<h3>Pokretanje</h3>
Moguće zastavice pri pokretanju:

Kratka zastavica |Duga zastavica | Pretpostavljena vrijednost | Značenje
:------------: | :-------------: |:-------------: | :-------------
-i | --input | in.po | ulazna datoteka sa grafom
-c | --config | config.txt | Ulazna datoteka sa skupom pravila
-t | --threads | 1 | Broj dretvi
-l | --limit | 10 | Maksimalan broj konsenzusa za generirati

Primjer izvođenja:
```
./conpoa -i ./test_data/20000_500_150.po  -c config.rules -t 4 -l 2
```
