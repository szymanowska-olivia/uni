import requests

BASE_URL = "http://127.0.0.1:5000"

def list_books():
    return requests.get(f"{BASE_URL}/books").json()

def add_book(data):
    return requests.put(f"{BASE_URL}/books", json=data).json()
