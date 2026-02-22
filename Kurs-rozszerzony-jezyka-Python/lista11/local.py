from database import Session
from models import Book

def list_books():
    with Session() as s:
        return [
            {
                "id": b.id,
                "title": b.title,
                "author": b.author,
                "year": b.year
            }
            for b in s.query(Book).all()
        ]


def add_book(data):
    with Session() as s:
        book = Book(**data)
        s.add(book)
        s.commit()
        return {
            "id": book.id,
            "title": book.title,
            "author": book.author,
            "year": book.year
        }

