import random

tekst1 = "" #tekst bez za dlugich wyarazow
tekst2 = "" #tekst o dobrej dlugosci bez za dlugich wyarazow

def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    global tekst1, tekst2
    word_cnt = 0
    slowa = tekst.split()
    for slowo in slowa:
        if len(slowo) <= dl_slowa:
            tekst1+= slowo
            tekst1+= " "
            word_cnt += 1
    
    tekst2 = tekst1
    if word_cnt > liczba_slow:
     idx_to_delete = set(random.sample(range(word_cnt), word_cnt - liczba_slow))
     tekst2 = tekst2.split()
     tekst2 = [tekst2[i] for i in range(word_cnt) if i not in idx_to_delete]
     tekst2 = " ".join(tekst2)

    


tekst = "Młodzieniec przestąpił próg do ciemnego przedpokoju, w którym\
za przegródką urządzono miniaturową kuchnię. Stara milczała, pytająco spoglądając na\
niego. Była to mała, zasuszona starucha w wieku lat sześćdziesięciu, o świdrujących,\
złych oczkach i małym, zadartym nosku. Wypłowiałe, jasne włosy były mocno\
wysmarowane tłuszczem. Dokoła cienkiej szyi, przypominającej\
29" #http://biblioteka.kijowski.pl/dostojewski%20fiodor/zbrodnia%20i%20kara.pdf

print("Oryginalny tekst:\n", tekst)

uprosc_zdanie(tekst, 10, 5)

print("\nTekst bez dlugich wyrazow:\n",tekst1)
print("\nTekst o dobrej dlugosci bez za dlugich wyrazow:\n",tekst2)