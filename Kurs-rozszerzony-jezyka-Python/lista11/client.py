import argparse
import api
import local

parser = argparse.ArgumentParser()
parser.add_argument("--api", action="store_true")

sub = parser.add_subparsers(dest="command")

add = sub.add_parser("add_book")
add.add_argument("--title", required=True)
add.add_argument("--author", required=True)
add.add_argument("--year", type=int, required=True)

lst = sub.add_parser("list_books")

args = parser.parse_args()
service = api if args.api else local

if args.command == "add_book":
    service.add_book({
        "title": args.title,
        "author": args.author,
        "year": args.year
    })
elif args.command == "list_books":
    books = service.list_books()
    for b in books:
        if isinstance(b, dict):
            print(b["id"], b["title"], b["author"], b["year"])
        else:
            print(b.id, b.title, b.author, b.year)
