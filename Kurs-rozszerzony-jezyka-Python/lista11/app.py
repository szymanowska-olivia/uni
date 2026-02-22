import argparse, json
from database import Session, init_db
from models import Book, Friend, Loan
from datetime import datetime



def seed_data():
    session = Session()
    if session.query(Book).count() == 0:
        with open("seed.json") as f:
            data = json.load(f)
            for b in data["books"]:
                session.add(Book(**b))
            for fnd in data["friends"]:
                session.add(Friend(**fnd))
            session.commit()
    session.close()


def add_book(args):
    with Session() as s:
        s.add(Book(title=args.title, author=args.author, year=args.year))
        s.commit()
        print("Book added")


def list_books(_):
    with Session() as s:
        for b in s.query(Book):
            print(b.id, b.title, b.author, b.year)


def loan_book(args):
    with Session() as s:
        active = s.query(Loan).filter(
            Loan.book_id == args.book_id,
            Loan.return_date == None
        ).first()

        if active:
            print("Book already loaned")
            return

        loan_date = datetime.strptime(args.loan_date, "%Y-%m-%d").date()

        s.add(Loan(
            book_id=args.book_id,
            friend_id=args.friend_id,
            loan_date=loan_date
        ))
        s.commit()
        print("Book loaned")


def return_book(args):
    with Session() as s:
        loan = s.get(Loan, args.loan_id)
        if loan and loan.return_date is None:
            return_date = datetime.strptime(args.return_date, "%Y-%m-%d").date()
            loan.return_date = return_date
            s.commit()
            print("Book returned")
        else:
            print("Invalid loan ID")


def main():
    init_db()
    seed_data()

    parser = argparse.ArgumentParser("Library system")
    sub = parser.add_subparsers()

    add = sub.add_parser("--add_book")
    add.add_argument("--title", required=True)
    add.add_argument("--author", required=True)
    add.add_argument("--year", type=int, required=True)
    add.set_defaults(func=add_book)

    lst = sub.add_parser("list_books")
    lst.set_defaults(func=list_books)

    loan = sub.add_parser("loan")
    loan.add_argument("--book_id", type=int, required=True)
    loan.add_argument("--friend_id", type=int, required=True)
    loan.add_argument("--loan_date", required=True)
    loan.set_defaults(func=loan_book)

    ret = sub.add_parser("return")
    ret.add_argument("--loan_id", type=int, required=True)
    ret.add_argument("--return_date", required=True)
    ret.set_defaults(func=return_book)

    args = parser.parse_args()
    if hasattr(args, "func"):
        args.func(args)
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
