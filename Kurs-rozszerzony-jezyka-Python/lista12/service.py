from models import Session, Book

# ====== BOOKS ======

def list_books():
    with Session() as s:
        return [b.to_dict() for b in s.query(Book).all()]

def add_book(data):
    with Session() as s:
        book = Book(**data)
        s.add(book)
        s.commit()
        s.refresh(book)
        return book.to_dict()

def get_book(book_id: int):
    with Session() as s:
        book = s.get(Book, book_id)
        return book.to_dict() if book else None

def delete_book(book_id: int):
    with Session() as s:
        book = s.get(Book, book_id)
        if not book:
            return False
        s.delete(book)
        s.commit()
        return True
