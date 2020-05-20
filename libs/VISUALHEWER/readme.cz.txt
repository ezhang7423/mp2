Visual Hever 1.0
(obsahuje brain Hewer24)

Spu�t�n�
--------
P�ed spu�t�n�m zkontrolujte, zda v adres��i spolu s programem je p��tomen soubor plocha.dat a tah.dat.


Proch�zen� stromu �e�en�
------------------------
Spus�e program. Na z�lo�ce Tree View m��ete proch�zet strom �e�en�. Ka�d� uzel je ohodnocen ��sly pn (proof number-po�et uzlu, ktere zbyva prohledat k dok�z�n� v�hry) a dn (disproof number - po�et uzl�, kter� zb�v� prohledat k dok�z�n� prohry). Nekone�no je ozna�eno jako -1. Uzel kter� ji� nelze rozbalit je koncov� a ohodnocovac� funkce v n�m ji� rozezn�, kdo vyhraje. Ve strom� se lze pohybovat my��, �i �ipkami kl�vesnice.


Tahy extern�ch AI
-----------------
Pro ka�dou situaci lze nahl�dnout, jak by hr�la v situaci pr�v� ozna�en�ho uzlu extern� AI a to stikem kl�ves 1-9 (v �asov�m limitu 1-9 sekund). 


Import a export situac�
-----------------------
Pr�v� aktivn� situaci lze exportovat do soubor� plocha.dat a tah.dat. Nebo lze importovat �pln� novou situaci jako ko�enovou.


Z�lo�ka Threat
--------------
Na z�lo�ce Threats jsou zobrazeny hrozby, kter� by vznilky po odehr�n� na dan� pol��ko, pro �ern�ho vlevo a b�l�ho vpravo se z-sou�asnic�(z je o��slov�na po ��dk�ch z=x+y*20). 
Cn=Po�et kamen�, kter� zb�v� polo�it do p�tice. Tn=Po�et kamen�, kter� zb�v� polo�it do neodvr�titelnosti hrozby, Tn bere ohled pouze na lok�ln� obrany, na glob�ln� proti�tok nikoliv.


Anal�za proher
--------------
Visual Hewer um� hr�t s extern�mi AI a po p��padn� proh�e analyzovat jej� d�vod (m�lo �asu na p�em��len� �i neobjeven� soupe�ova tahu moveger�torem). Tato funkce ov�em d�lala z�ke�n� chyby a z�hadn�, tak�e je v t�to verzi znemo�n�na.


Ostatn�
-------
Move gener�tor je naprosto stejn� jako u Hewer24, kter� se ��astnil turnaje Gomocup 2004, mal� zjednodu�en� kv�li p�ehlednosti je u inicializace pn a dn.


Slabiny programu
----------------
�patn� za��tek, chyb� openbook (dal�� d�vod �patn�ho zah�jen�), nedokonal� uhodnocovac� funkce (�patn� hra ve st�edn� f�zi). A dal�� obecn� nedostatky pn-search algoritmu (AI neum� br�nit, pouze �to�it, p�ece�ov�n� pn a dn, probl�my s pam�t�).

Siln� str�nky
-------------
V koncovk�ch um� nal�zt v�hru i 19 tah� dop�edu (p�i 5 sekund�ch na celeronu 400Mhz). Rychl� a p�esn� ohodnocovac� funkce, p�esn� movegener�tor p�i obran�.


Tom� Kube�
5.4. 2004
<tomas_kubes@seznam.cz>