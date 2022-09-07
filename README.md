# distancesum

Horváth Bence
distancesum feladat

Mivel elfelejtettem az elejétől a githubot használni, ezért ezt a dokumentációt írtam helyette.

Az elején a feladatot átgondolva úgy döntöttem, hogy a Dijkstra algoritmussal keresem meg a legrövidebb utakat, mivel fel kell tárni az utat minden pontra.
Eleinte úgy gondoltam, hogy elég lesz egy 2 dimenziós karaktertömböt tárolni és ezen lefuttatni azalgoritmust, de ezt átgondolva túl bonyolult és átláthatatlan lett volna az algoritmus, ezért a tömb segítségével létrehoztam egy irányított gráfot.
A Dijkstra algoritmustól annyival térek el, hogy nem törlöm ki a pontokat rögtön a tömbből, hogy később fel tudjam szabadítani a pontokat.
Félreértettem a feladatot és nem az összes hexa számba kerestem a legrövidebb utak hosszának összegét, hanem a C pontba kerestem az összes legrövidebb utak hosszát. Ezt a Dijkstra algoritmus lefutása után egy rekurzív függvénnyel oldottam meg, ami eleinte belépett egy pontba és megnézte, hogy melyik szomszédoknak kisebb az addigi úthossz. Ha kisebb akkor azon a ponton is meghívódott ez a függvény. Akkor tért vissza a függvény 1-gyel, ha a pont távolsága 0 volt. Ezeket összeadta és ha nem 0 volt az értéke a pontnak, akkor ezeknek az összegét adta vissza. A végső visszatérési értéket a legrövidebb út hosszával összeszorozva megkaptam a félreértett feladatra a választ (1995).
De észrevettem a hibámat és kijavítottam úgy, hogy a gráf felépítése közben eltárolom külön a hexa számmal megjelölt pontokat és a Dijkstra algoritmus lefutása után, mindegyikből kivonok 1-et és az összegük a megoldás.
