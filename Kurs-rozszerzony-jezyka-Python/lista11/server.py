from flask import Flask, request, jsonify
from database import Session, init_db
from models import Book

app = Flask(__name__)
init_db()

@app.route("/books", methods=["GET"])
def list_books():
    with Session() as s:
        books = s.query(Book).all()
        return jsonify([
            {"id": b.id, "title": b.title, "author": b.author, "year": b.year}
            for b in books
        ])

@app.route("/books/<int:book_id>", methods=["GET"])
def get_book(book_id):
    with Session() as s:
        b = s.get(Book, book_id)
        if not b:
            return jsonify({"error": "not found"}), 404
        return jsonify({"id": b.id, "title": b.title, "author": b.author, "year": b.year})

@app.route("/books", methods=["PUT"])
def add_book():
    data = request.json
    with Session() as s:
        book = Book(**data)
        s.add(book)
        s.commit()
        return jsonify({"msg": "created", "id": book.id})

@app.route("/books/<int:book_id>", methods=["POST"])
def update_book(book_id):
    data = request.json
    with Session() as s:
        book = s.get(Book, book_id)
        if not book:
            return jsonify({"error": "not found"}), 404
        for k, v in data.items():
            setattr(book, k, v)
        s.commit()
        return jsonify({"msg": "updated"})

@app.route("/books/<int:book_id>", methods=["DELETE"])
def delete_book(book_id):
    with Session() as s:
        book = s.get(Book, book_id)
        if not book:
            return jsonify({"error": "not found"}), 404
        s.delete(book)
        s.commit()
        return jsonify({"msg": "deleted"})

if __name__ == "__main__":
    app.run()
