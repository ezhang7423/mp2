Visual Hever 1.0
(obsahuje brain Hewer24)

Spuštìní
--------
Pøed spuštìním zkontrolujte, zda v adresáøi spolu s programem je pøítomen soubor plocha.dat a tah.dat.


Procházení stromu øešení
------------------------
Spuse program. Na záloce Tree View mùete procházet strom øešení. Kadı uzel je ohodnocen èísly pn (proof number-poèet uzlu, ktere zbyva prohledat k dokázání vıhry) a dn (disproof number - poèet uzlù, která zbıvá prohledat k dokázání prohry). Nekoneèno je oznaèeno jako -1. Uzel kterı ji nelze rozbalit je koncovı a ohodnocovací funkce v nìm ji rozezná, kdo vyhraje. Ve stromì se lze pohybovat myší, èi šipkami klávesnice.


Tahy externích AI
-----------------
Pro kadou situaci lze nahlédnout, jak by hrála v situaci právì oznaèeného uzlu externí AI a to stikem kláves 1-9 (v èasovém limitu 1-9 sekund). 


Import a export situací
-----------------------
Právì aktivní situaci lze exportovat do souborù plocha.dat a tah.dat. Nebo lze importovat úplnì novou situaci jako koøenovou.


Záloka Threat
--------------
Na záloce Threats jsou zobrazeny hrozby, které by vznilky po odehrání na dané políèko, pro èerného vlevo a bílého vpravo se z-souøasnicí(z je oèíslována po øádkách z=x+y*20). 
Cn=Poèet kamenù, které zbıvá poloit do pìtice. Tn=Poèet kamenù, které zbıvá poloit do neodvrátitelnosti hrozby, Tn bere ohled pouze na lokální obrany, na globální protiútok nikoliv.


Analıza proher
--------------
Visual Hewer umí hrát s externími AI a po pøípadné prohøe analyzovat její dùvod (málo èasu na pøemıšlení èi neobjevení soupeøova tahu movegerátorem). Tato funkce ovšem dìlala zákeøné chyby a záhadné, take je v této verzi znemonìna.


Ostatní
-------
Move generátor je naprosto stejnı jako u Hewer24, kterı se úèastnil turnaje Gomocup 2004, malá zjednodušení kvùli pøehlednosti je u inicializace pn a dn.


Slabiny programu
----------------
Špatnı zaèátek, chybí openbook (další dùvod špatného zahájení), nedokonalá uhodnocovací funkce (špatná hra ve støední fázi). A další obecné nedostatky pn-search algoritmu (AI neumí bránit, pouze útoèit, pøeceòování pn a dn, problémy s pamìtí).

Silné stránky
-------------
V koncovkách umí nalézt vıhru i 19 tahù dopøedu (pøi 5 sekundách na celeronu 400Mhz). Rychlá a pøesná ohodnocovací funkce, pøesnı movegenerátor pøi obranì.


Tomáš Kubeš
5.4. 2004
<tomas_kubes@seznam.cz>