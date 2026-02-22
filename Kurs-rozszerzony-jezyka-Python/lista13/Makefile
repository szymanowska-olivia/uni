
.PHONY: test pep8 types all

# Uruchom wszystkie testy jednostkowe
test:
	python -m unittest discover tests

# Sprawdzenie zgodności z PEP8
pep8:
	pycodestyle data_access.py tests

# Sprawdzenie adnotacji typów
types:
	mypy data_access.py

# Wszystko naraz
all: test pep8 types
