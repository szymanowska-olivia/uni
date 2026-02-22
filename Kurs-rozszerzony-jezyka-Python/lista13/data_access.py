import requests
from server import Book, Borrow, Friend, Session, engine
from typing import Any
import shelve

API_URL = "http://localhost:5000"


def api_add_book(new_year: int, new_author: str, new_title: str):
    """
    Creates a request to add a book via the API
    Args: new_year, new_author, new_title
    """
    data: dict[str, Any] = {}
    data["year"] = new_year
    data["author"] = new_author
    data["title"] = new_title
    res = requests.put(f"{API_URL}/book/", json=data)
    print(res.json())


def api_list_books():
    """
    Creates a request to list all books via the API
    """
    res = requests.get(f"{API_URL}/book/")
    print(res.json())


def api_update_book(
        book_id: int,
        new_year: int,
        new_author: str,
        new_title: str):
    """
    Creates a request to update a book with a given id via the API
    Args: book_id, new_year, new_author, new_title
    """
    data: dict[str, Any] = {}
    data["year"] = new_year
    data["author"] = new_author
    data["title"] = new_title
    res = requests.post(f"{API_URL}/book/{book_id}", json=data)
    print(res.json())


def api_delete_book(book_id: int):
    """
    Creates a request to delete a book with a given id via the API
    Args: book_id
    """
    res = requests.delete(f"{API_URL}/book/{book_id}")
    print(res.json())


def api_add_friend(new_name: str, new_email: str, new_phone_number: str):
    """
    Creates a request to add a friend via the API
    Args: new_name, new_email, new_phone_number
    """
    data = {}
    data["name"] = new_name
    data["email"] = new_email
    data["phone_number"] = new_phone_number
    res = requests.put(f"{API_URL}/friend/", json=data)
    print(res.json())
    clear_cache()


def api_list_friends():
    """
    Creates a request to list all friends via the API
    """
    res = requests.get(f"{API_URL}/friend/")
    print(res.json())


def api_update_friend(
        friend_id: int,
        new_name: str,
        new_email: str,
        new_phone_number: str):
    """
    Creates a request to update a friend via the API
    Args: friend_id, new_name, new_email, new_phone_number
    """
    data = {}
    data["phone_number"] = new_phone_number
    data["name"] = new_name
    data["email"] = new_email
    res = requests.post(f"{API_URL}/friend/{friend_id}", json=data)
    print(res.json())
    clear_cache()


def api_delete_friend(friend_id: int):
    """
    Creates a request to delete a friend with a given id via the API
    Args: friend_id
    """
    res = requests.delete(f"{API_URL}/friend/{friend_id}")
    print(res.json())
    clear_cache()


def api_borrow_book(book_id: int, friend_id: int, borrow_date: str):
    """
    Creates a request to create a new borrow record
    Args: book_id, friend_id, borrow_date
    """
    res = requests.put(
        f"{API_URL}/borrows/{book_id}/{friend_id}/{borrow_date}")
    print(res.json())


def api_return_book(borrow_id: int, return_date: str):
    """
    Creates a request to return a book
    Args: borrow_id, return_date
    """
    res = requests.post(f"{API_URL}/borrows/{borrow_id}/{return_date}")
    print(res.json())


def api_list_borrows():
    """
    Creates a request to list all borrow records
    """
    res = requests.get(f"{API_URL}/borrows/")
    print(res.json())


def db_add_book(new_year: int, new_author: str, new_title: str):
    """
    Adds a new book to the database
    Args: new_year, new_author, new_title
    """
    book = Book(year=new_year, author=new_author, title=new_title)
    with Session(engine) as session:
        session.add(book)
        session.commit()
        print("A new book has been added!")


def db_list_books():
    """
    Lists all books from the database
    """
    with Session(engine) as session:
        books = session.query(Book)
        for book in books:
            print(f"{book.id}: {book.author}, {book.title}, {book.year}")


def db_update_book(
        book_id: int,
        new_year: int,
        new_author: str,
        new_title: str):
    """
    Updates a book with a given id in the database
    Args: book_id, new_year, new_author, new_title
    """
    with Session(engine) as session:
        book = session.get(Book, book_id)
        if not book:
            print("This book does not exist!")
            return
        if new_title:
            book.title = new_title
        if new_year:
            book.year = new_year
        if new_author:
            book.author = new_author
        session.commit()
        print("A book has been updated!")


def db_delete_book(book_id: int):
    """
    Deletes a book with a given id from the database
    Args: book_id
    """
    with Session(engine) as session:
        book = session.get(Book, book_id)
        if book:
            session.delete(book)
            session.commit()
            print("A book has been deleted!")
        else:
            print("This book does not exist!")


def db_add_friend(new_name: str, new_email: str, new_phone_number: str):
    """
    Adds a new friend to the database
    Args: new_name, new_email, new_phone_number
    """
    friend = Friend(
        name=new_name,
        email=new_email,
        phone_number=new_phone_number)
    with Session(engine) as session:
        session.add(friend)
        session.commit()
        print("A new friend has been added!")


def db_list_friends():
    """
    Lists all friends from the database
    """
    with Session(engine) as session:
        friends = session.query(Friend)
        for friend in friends:
            print(f"{friend.id}: {friend.name}, "
                  f"{friend.email}, {friend.phone_number}")


def db_update_friend(
        friend_id: int,
        new_name: str,
        new_email: str,
        new_phone_number: str):
    """
    Updates a friend with a given id in the database
    Args: friend_id, new_name, new_email, new_phone_number
    """
    with Session(engine) as session:
        friend = session.get(Friend, friend_id)
        if not friend:
            print("This friend does not exist!")
            return
        if new_name:
            friend.name = new_name
        if new_email:
            friend.email = new_email
        if new_phone_number:
            friend.phone_number = new_phone_number
        session.commit()
        print("A friend has been updated!")




def db_list_borrows():
    """
    Lists all borrow records in the database
    """
    with Session(engine) as session:
        borrows = session.query(Borrow)
        if borrows.first() is None:
            print("No borrow records found!")
        for borrow in borrows:
            print(f"{borrow.id}: {borrow.friend_id}, {borrow.book_id}, "
                  f"{borrow.borrow_date}, {borrow.return_date}")


USERS = {
    "admin": "admin123",
    "user": "user123"
}

_curr_us = None


def login(username: str, password: str) -> bool:
    global _curr_us
    if USERS.get(username) == password:
        _curr_us = username
        return True
    raise ValueError("Invalid credentials")


def logout() -> None:
    global _curr_us
    _curr_us = None


def login_required(func):
    def wrapper(*args, **kwargs):
        if _curr_us is None:
            raise PermissionError("User not logged in")
        return func(*args, **kwargs)
    return wrapper


def cache(func):
    def wrapper(*args, **kwargs):
        key = f"{func.__name__}:{args}:{kwargs}"

        with shelve.open("cache.db") as db:
            if key in db:
                return db[key]

            result = func(*args, **kwargs)
            db[key] = result
            return result

    return wrapper

def clear_cache():
    with shelve.open("cache.db") as db:
        db.clear()


@cache
def get_friend_by_id(friend_id: int):
    with Session(engine) as session:
        return session.get(Friend, friend_id)

@login_required
def db_delete_friend(friend_id: int) -> None:
    with Session(engine) as session:
        friend = session.get(Friend, friend_id)
        if friend:
            session.delete(friend)
            session.commit()
