import re
import string

def is_palindrom(text):
    translator = str.maketrans('', '', string.punctuation) #zamiana znakow,usuniecie
    text_without = text.translate(translator)
    text_without = re.sub(r'\s+', '', text_without)
    text_without = text_without.lower()
    text_without_rev = text_without[::-1] #co ile i w ktora strone
    print(text_without)
    return (text_without_rev == text_without)

text = "Eine güldne, gute Tugend: Lüge ni"

print(is_palindrom(text))
