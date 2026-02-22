import requests
from bs4 import BeautifulSoup
from collections import Counter, defaultdict


def fetch_page_text(url):
    """Pobiera tekst ze strony. Zwraca tekst lub None w przypadku błędu."""
    try:
        response = requests.get(url, timeout=5)
        response.raise_for_status()
        soup = BeautifulSoup(response.text, "html.parser")
        return soup.get_text(separator=" ").lower()

    except requests.exceptions.RequestException as e:
        print(f"[BŁĄD] Nie udało się pobrać strony {url}: {e}")
        return None


def build_index(urls):
    """Buduje indeks słów i lokalizacje wystąpień na podstawie listy URLi."""
    word_index = Counter()
    word_locations = defaultdict(list)

    for url in urls:
        print(f"Pobieram: {url}")
        text = fetch_page_text(url)

        if text is None:
            continue  # pomiń stronę jeśli był błąd

        words = [
            word for word in text.split()
            if word.isalpha()
        ]

        # zliczanie wystąpień
        word_index.update(words)

        # zapis stron, na których występują słowa
        for word in set(words):
            word_locations[word].append(url)

    print("Indeksowanie zakończone.\n")
    return word_index, word_locations


def most_common_word(word_index):
    """Zwraca najpopularniejsze słowo (lub None)."""
    if not word_index:
        return None, 0
    return word_index.most_common(1)[0]


def find_word(word_locations, word):
    """Zwraca listę stron, na których dane słowo występuje."""
    return word_locations.get(word.lower(), [])


# ------------------------------
# PRZYKŁADOWE UŻYCIE
# ------------------------------

if __name__ == "__main__":
    urls = [
        "https://www.python.org/",
        "https://pl.wikipedia.org/wiki/Python",
        "https://www.openai.com/"
    ]

    word_index, word_locations = build_index(urls)

    # najpopularniejsze słowo
    word, count = most_common_word(word_index)
    print(f"Najpopularniejsze słowo: '{word}' ({count} wystąpień)")

    # wyszukanie słowa
    search = "python"
    pages = find_word(word_locations, search)

    print(f"\nSłowo '{search}' występuje na stronach:")
    for p in pages:
        print(" -", p)
