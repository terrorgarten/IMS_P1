# IMS - 7. Šírení emisí v atmosfére
*Šírenie emisií z najväčších fabrík v Prahe*

#### Príkaz na preloženie :
*$make*

#### Príkaz na spustenie:
*$./ims [-g] [-p] [-w <wind>] [-i <iterations>] [-m <i1:i2>]*\
\
Kde:
- g	- Spustenie programu s GUI
- p - Polovica fabrík sa po 12tich iteráciách zastaví a po 12tich iteráciách  znova spustí
- w <wind\> - Smer vetra: 0 (žiadny), 1 (N), 2 (S), 3 (E), 4 (W), 5 (NE), 6 (NW),
			7 (SE), 8(SW)
- i <iterations\> - Počet iterácií programu, v GUI módu ignorováno
- m <i1:i2\> - Bunka na pozorovanie, i1 - index1 a i2 - index2 v poli buniek