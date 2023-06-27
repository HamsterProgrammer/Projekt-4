# Projekt-4
## OPIS DLA UŻYTKOWNIKA
Program służy do układania kontenerów o różnych kształtach za pomocą dźwigu. 
Podnosić może jedynie 3 kształty: kwadraty, trójkąty i okręgi.
Dźwig ogranicza również masa podnoszonego elementu która wynosi domyślnie 100.
Użytkownik może układać wieże składająca się jedynie z tych samych kształtów.
Istnieje również opcja ułożenia wieży za użytkownika składającej się z wszystkich 3 kształtów
Użytkownik może dowolnie zmieniać maksymalną dopuszczalną masę, jaką dźwig może podnieść 
    *MENU - Options - Set Mass - w oknie dialogowym wpisz żądaną mase*
Użytkownik może dodać dowolną figurę w losowym miejscu o losowej masie. 
    *MENU - Draw - Circle/Box/Triangle*
### STEROWANIE:
*Strzałki - poruszanie dźwigiem
*Enter - podnoszenie/opuszczanie kontenera

## OPIS DZIAŁANIA PROGRAMU
Program jest napisany przy użyciu OOP. 
Istnieje klasa kształtu, która opisuje współrzędne i masy. Dane są przechowywane w osobnych wektorach dla każdego typu kształtu.
Jest też klasa robotów. w którym znajdują się dane dotyczące stanu dzwigu, maksymalnego i minimalnego położenia oraz ciężaru, jaki może podnieść. 
Są też funkcje sprawdzające, czy współrzędna, do której chce się przenieść wskazówka, jest „dozwolona” oraz funkcja zmiany maksymalnej masy.

Na początku inicjalizacji programu tworzone są po trzy figury każdego typu (circles, boxes and triangles), o ustalonych masach i współrzędnych.
Przy podalszym dodawaniu figur masy i współrzędne są generowane pseudolosowo.

Budując wieżę z elementów, ręka szuka odpowiedniego elementu spośród istniejących, sprawdzając go według kryteriów masy i położenia (np. czy jest jeszcze coś nad nią, czy jest na samej gorzę)
