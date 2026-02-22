import decimal as d

vat = 0.23
vat2 = d.Decimal('0.23')

def vat_faktura(lista):
    suma = 0
    for netto in lista:
        suma+=netto

    suma*=vat2
    return suma

def vat_paragon(lista):
    suma = 0
    for netto in lista:
        suma += netto * vat2
    return suma

zakupy = [0.1, 0.456, 0.789, 0.98765]

zakupy2 = [d.Decimal(str(x)) for x in zakupy]

print(vat_faktura(zakupy2))
print(vat_paragon(zakupy2))
print(vat_faktura(zakupy2) == vat_paragon(zakupy2))


