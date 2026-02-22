import argparse
from flask import Flask, jsonify, request
import service
from models import init_db

# ====== INIT ======

init_db()
app = Flask(__name__)

# ====== REST API ======

@app.route("/books", methods=["GET"])
def api_list_books():
    return jsonify(service.list_books())

@app.route("/books", methods=["PUT"])
def api_add_book():
    return jsonify(service.add_book(request.json)), 201

@app.route("/books/<int:book_id>", methods=["GET"])
def api_get_book(book_id):
    book = service.get_book(book_id)
    if not book:
        return jsonify({"error": "not found"}), 404
    return jsonify(book)

@app.route("/books/<int:book_id>", methods=["DELETE"])
def api_delete_book(book_id):
    if service.delete_book(book_id):
        return jsonify({"msg": "deleted"})
    return jsonify({"error": "not found"}), 404

# ====== CLI ======

def cli():
    parser = argparse.ArgumentParser("Library")
    sub = parser.add_subparsers(dest="cmd")

    add = sub.add_parser("add")
    add.add_argument("--title", required=True)
    add.add_argument("--author", required=True)
    add.add_argument("--year", type=int, required=True)

    lst = sub.add_parser("list")

    args = parser.parse_args()

    if args.cmd == "add":
        book = service.add_book(vars(args))
        print("Added:", book)

    elif args.cmd == "list":
        for b in service.list_books():
            print(b["id"], b["title"], b["author"], b["year"])
    else:
        parser.print_help()

# ====== ENTRYPOINT ======

if __name__ == "__main__":
    cli()
    # albo:
    # app.run()
