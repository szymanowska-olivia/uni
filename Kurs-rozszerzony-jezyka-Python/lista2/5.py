import re

def kompresja (tekst):
    lista_par = [] 
    tekst = re.findall(r'\S+|\s+', tekst)
    for slowo in tekst:
        char_cnt = 1
        prev_znak = slowo[0]
        for znak in slowo[1:]:
            if prev_znak == znak:
                char_cnt += 1
            else: 
                lista_par.append((char_cnt, prev_znak))
                char_cnt = 1
                prev_znak = znak
        lista_par.append((char_cnt, prev_znak))
    return lista_par

def dekompresja(tekst_skompresowany):
    tekst_zdekompresowany = ""
    for cnt_znak,znak in tekst_skompresowany:
        tekst_zdekompresowany += cnt_znak * znak

    return tekst_zdekompresowany

tekst = "suuuuuper"
#http://biblioteka.kijowski.pl/dostojewski%20fiodor/zbrodnia%20i%20kara.pdf

tekst_komp = kompresja(tekst)
tekst_dekomp = dekompresja(tekst_komp)

print(tekst)
print("\n",tekst_komp)
print("\n",tekst_dekomp)

