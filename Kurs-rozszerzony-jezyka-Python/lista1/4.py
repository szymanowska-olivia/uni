import random
import decimal as d

liczba_losowan = 10000


promien = 1

ltwo = 0
cltwt = 0

for i in range (liczba_losowan):
   y = d.Decimal(str(random.uniform(-1,1)))
   x = d.Decimal(str(random.uniform(-1,1)))

   if x*x + y*y <= promien*promien:
        ltwo += 1
   cltwt += 1

   print("pi approximation =", d.Decimal(4) * d.Decimal(ltwo) / d.Decimal(cltwt))


