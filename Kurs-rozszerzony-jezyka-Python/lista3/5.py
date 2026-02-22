from itertools import permutations

def rozwiazywanie_zadania(word1, word2, result_word, op):

    letters = set(word1 + word2 + result_word)
    if len(letters) > 10:
        return  
    
    ops = {'+': lambda a, b: a + b, '-': lambda a, b: a - b, '*': lambda a, b: a * b, '/': lambda a, b: a / b}    
    f = ops[op]
    
    for perm in permutations(range(10), len(letters)):
        mapping = dict(zip(letters, perm))
        
        if mapping[word1[0]] == 0 or mapping[word2[0]] == 0 or mapping[result_word[0]] == 0:
            continue
        
        n1 = int(''.join(str(mapping[c]) for c in word1))
        n2 = int(''.join(str(mapping[c]) for c in word2))
        res = int(''.join(str(mapping[c]) for c in result_word))
        
        if f(n1, n2) == res:
           yield mapping  

def wyswietl_rozwiazanie(mapping, word1, word2, result_word, op):
    n1 = ''.join(str(mapping[c]) for c in word1)
    n2 = ''.join(str(mapping[c]) for c in word2)
    res = ''.join(str(mapping[c]) for c in result_word)
    
    width = max(len(word1), len(word2), len(result_word)) + 2
    width2 = max(len(n1), len(n2), len(res)) + 2


    print(word1.rjust(width))
    print(op + " "+ word2.rjust(width - 2))
    print("-" * width)
    print(result_word.rjust(width),"\n")

    print(n1.rjust(width2))
    print(op + " "+ n2.rjust(width2 - 2))
    print("-" * width2)
    print(res.rjust(width2),"\n")

    print(f"Mapowanie liter: {mapping}", "\n")

word1 = "KIOTO"
word2 = "OSAKA"
result_word = "TOKIO"
op = "+"
    
for rozw in rozwiazywanie_zadania(word1, word2, result_word, op):
    wyswietl_rozwiazanie(rozw, word1, word2, result_word, op)


