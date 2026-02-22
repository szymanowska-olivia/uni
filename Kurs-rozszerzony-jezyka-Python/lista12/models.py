from __future__ import annotations
from sqlalchemy import create_engine, Integer, String, ForeignKey, Date
from sqlalchemy.orm import DeclarativeBase, sessionmaker, relationship, Mapped, mapped_column, validates
from datetime import date

# ====== SQLAlchemy setup ======

engine = create_engine("sqlite:///library.db")
Session = sessionmaker(bind=engine)

class Base(DeclarativeBase):
    pass

# ====== MODELE ======

class Book(Base):
    __tablename__ = "books"

    id: Mapped[int] = mapped_column(primary_key=True)
    title: Mapped[str]
    author: Mapped[str]
    year: Mapped[int]

    @validates("year")
    def validate_year(self, _, year):
        if year < 0:
            raise ValueError("Year must be positive")
        return year

    def to_dict(self):
        return {
            "id": self.id,
            "title": self.title,
            "author": self.author,
            "year": self.year
        }

class Friend(Base):
    __tablename__ = "friends"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str]
    email: Mapped[str]
    phone: Mapped[str]

class Loan(Base):
    __tablename__ = "loans"

    id: Mapped[int] = mapped_column(primary_key=True)
    book_id: Mapped[int] = mapped_column(ForeignKey("books.id"))
    friend_id: Mapped[int] = mapped_column(ForeignKey("friends.id"))
    loan_date: Mapped[date]
    return_date: Mapped[date | None] = mapped_column(nullable=True)

# ====== INIT ======

def init_db():
    Base.metadata.create_all(engine)
